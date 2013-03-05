/**
	parse.cpp: 进行语法分析和语义分析
	//test
	int area, r;
	area  r * (r + r);
*/

#include "compiler.h"
#include "util.h"
#include <iostream>
#include <fstream>
using namespace std;

// 定义语法，语义分析时栈的最大长度
#define STACK_SIZE 100

// 引入全局变量
extern IdTable g_idTable;
extern Action g_actions[23][10];
extern Goto g_gotos[12];
extern Production pros[13];

// 声明 产生新的临时变量
int g_tempIndex = 0;
int NewTemp(); // 声明产生新变量的函数
Token g_lastToken(-1, -1, -1); // 保留上一个词法单元
bool isNeedLastToken = false; // 记录是否需要调用上一个词法单元

// 声明打印四元式的函数
void PrintEmit(char *op, char *arg1, char *arg2, char *result);

// 声明 错误个数
int g_errorNum = 0;

// PrintError
void PrintError(const char *errorMsg, const int &row, const int &col);

/**
	语法分析和语义分析的主函数
*/
int parse(const char *filePath)
{
	ifstream infile(filePath, ios::in);
	// test the file is exit
	if(!infile)
	{
		cerr << ">\n>Sorry, cannot open " << filePath << " !\n>"<< endl;
		exit(0);
	}

	// 声明语法，语义分析中用到的栈
	Stack<int> s_state(STACK_SIZE); // 状态栈
	Stack<int> s_token(STACK_SIZE); // 符号栈
	Stack<int> s_seman(STACK_SIZE); // 语义栈

	// 记录此法分析的行列数
	int row = 1;
	int col = 0;
	Token token(-1, row, col);
	Action action;
	int expNum = 0;
	while(true)
	{
		if(isNeedLastToken != true)
		{
			if(scan(infile, token, row, col) == EOF)
			{
				break;
			}
		}
		else
		{
			isNeedLastToken = false;
			token = g_lastToken;
		}

		// 初始化栈
		s_state.Clear();s_state.Push(0);
		s_token.Clear();s_token.Push(Tag::SEMICOLON);
		s_seman.Clear();s_seman.Push(-1); // -1代表‘_’

		// for 输出显示, I hate it !
		expNum++;
		printf("\n=======================================================================================\n");
		printf(">开始编译第%d条语句：\n", expNum);
		printf("--------------------\n");
		printf("状态栈\t\t\t\t符号栈\t\t\t动作\n");

		while(true)
		{
			//====================================================================
			// 打印词素到屏幕，可以不用，for test
			/*if(token.tag != 9)
			{
				printf("(%s,_)\n", Tag::words[token.tag]);
			}
			else
			{
				printf("(%s,%d)\n",Tag::words[token.tag], g_idTable.idTableIndex);
			}*/
			//=====================================================================


			// 打印栈信息
			ShowStacks(s_state, s_token);

			// 当前动作
			action = g_actions[s_state.Peek()][token.tag];

			// 移进
			if('s' == action.a)
			{
				s_state.Push(action.i);
				s_token.Push(token.tag);
				// 如果是ID，则移进 g_idTable.idTableIndex
				s_seman.Push((token.tag == Tag::ID) ? g_idTable.idTableIndex : token.tag);
				PrintAction(action);
				cout << endl;
				if(isNeedLastToken != true)
				{
					// 得到下一个字符，并检错是否非法结束
					if(scan(infile, token, row, col) == EOF)
					{
						g_errorNum++;
						PrintError("当前位置缺少\";\"", row, col);
						break;
					}
				}
				else
				{
					isNeedLastToken = false;
					token = g_lastToken;
				}
			}
			// 规约
			else if('r' == action.a)
			{
				PrintAction(action);

				// 先处理 状态栈 和 符号栈，即语法分析
				int p_l = pros[action.i].length;
				for(int i = 0; i < p_l; i++)
				{
					s_state.Pop();
					s_token.Pop();
				}
				// 把规约元素入 符号栈
				s_token.Push(pros[action.i].head);

				// 把goto表中的相应元素入状态栈
				s_state.Push(FindGoto(s_state.Peek(), pros[action.i].head, g_gotos));

				// 处理 语义子程序
				switch(action.i)
				{
				case 12: // F → id
					// { p = loolup(id.name); F.place = p; }
					break;
				case 10: // T → F
					// { T.place = F.place; }
					break;
				case 11: // F → ( E )
					{// { F.place = E.place; }
						s_seman.Pop(); // pop ')'
						int f_place = s_seman.Pop();
						s_seman.Pop(); // pop '('
						s_seman.Push(f_place);
					}
					break;
				case 8: // E → T
					// { E.place = T.place; }
					break;
				case 7: // E → E' + T
					{// { E.PALCE=newtemp();emit(+，E(1).PLACE，T.PLACE，E.PLACE)}
						int e_place = NewTemp();
						int t_place = s_seman.Pop();
						s_seman.Pop(); // pop '+'
						int e1_place = s_seman.Pop();
						s_seman.Push(e_place);
						PrintEmit("+", g_idTable.idTable[e1_place].name, g_idTable.idTable[t_place].name, g_idTable.idTable[e_place].name);
					}
					break;
				case 9:// T → T(1) * F
					{// { T.PLACE=newtemp(); emit(*，T(1).PLACE，F.PLACE，T.PLACE)}
						int t_place = NewTemp();
						int f_place = s_seman.Pop();
						s_seman.Pop(); // pop '*'
						int t1_place = s_seman.Pop();
						s_seman.Push(t_place);
						PrintEmit("*", g_idTable.idTable[t1_place].name, g_idTable.idTable[f_place].name, g_idTable.idTable[t_place].name);
					}
					break;
				case 6:// A → id = E //；
					{// { p=lookup(id.name); emit（=,E.PLACE , _,p）;}
						int e_place = s_seman.Pop();
						s_seman.Pop(); // pop '='
						int id_place = s_seman.Pop();
						s_seman.Push(id_place);
						PrintEmit("=", g_idTable.idTable[e_place].name, "_", g_idTable.idTable[id_place].name);
					}
					break;
				case 5:// D → D（1），id
					{// { fill(id,D(1).att);D.att=D(1).att; }
						int id_tag = s_seman.Pop();
						s_seman.Pop(); //pop ','
						int d_att = s_seman.Peek();
						strcpy_s(g_idTable.idTable[id_tag].type, Tag::words[d_att]);
						cout << " { " << g_idTable.idTable[id_tag].name << ".type = "<< Tag::words[d_att] <<" }";
					}
					break;
				case 3:// D → int id
					{// { fill（id，int）；D.att=int; }
						int id_tag = s_seman.Pop();
						int d_att = s_seman.Peek();
						strcpy_s(g_idTable.idTable[id_tag].type, Tag::words[d_att]);
						cout << " { " << g_idTable.idTable[id_tag].name << ".type = int }";
					}
					break;
				case 4:// D → float id
					{// { fill（id，float）；D.att=float; }
						int id_tag = s_seman.Pop();
						int d_att = s_seman.Peek();
						strcpy_s(g_idTable.idTable[id_tag].type, Tag::words[d_att]);
						cout << " { " << g_idTable.idTable[id_tag].name << ".type = float }";
					}
					break;
				case 2:// S → A //；
					break;
				case 1:// S → D //；
					break;
				default:
					break;
				}
				cout << endl;
			}
			// 接受
			else if('a' == action.a)
			{
				cout << "accept ^_^" << endl;
				break; // 结束本条语句
			}
			else if('e' == action.a)
			{
				g_errorNum++;

				PrintAction(action);
				cout << endl;

				// 0 == action.i : // 不会出现此错误，e0 只是为了填表
				if(1 == action.i || 0 == action.i || 2 == action.i)
				{	// 当前符号多余，删除
					char e_m[40];
					if(action.i == 2)
					{
						strcpy_s(e_m, "右括号不匹配");
					}
					else
					{
						strcpy_s(e_m, " \"");
						if(Tag::ID == token.tag)
							strcat_s(e_m, g_idTable.idTable[g_idTable.idTableIndex].name);
						else
							strcat_s(e_m, Tag::words[token.tag]);
						strcat_s(e_m, "\" ");
						strcat_s(e_m, "当前符号多余，需要删除");
					}
					PrintError(e_m, row, col);
					if(scan(infile, token, row, col) == EOF)
					{
						PrintError("当前位置缺少\";\"", row, col);
						break;
					}
					continue;
				}
				else if(action.i >= 5 && action.i <= 8)
				{					
					// 新建临时变量 id, 并存入语义栈
					s_seman.Push(NewTemp());
					s_token.Push(Tag::ID);
					int shiftState;
					switch(action.i)
					{
					case 5:
						shiftState = 8; break;
					case 6:
						shiftState = 9; break;
					case 7:
						shiftState = 11; break;
					case 8:
						shiftState = 16; break;
					}
					s_state.Push(shiftState);
					PrintError("缺少标识符！", row, col);
				}
				else if(action.i == 12)
				{
					// 规约时缺少 ";"
					g_lastToken = token;
					token.setAll(Tag::SEMICOLON, row, col);
					isNeedLastToken = true;
					PrintError("当前位置缺少\";\"!", row, col);
				}
				else if(action.i == 13)
				{
					// 规约时缺少 ","
					g_lastToken = token;
					token.setAll(Tag::COMMA, row, col);
					isNeedLastToken = true;
					PrintError("当前位置缺少\",\"!", row, col);
				}
				else if(action.i == 14)
				{
					// 规约时缺少 ","
					g_lastToken = token;
					token.setAll(Tag::PLUS, row, col);
					isNeedLastToken = true;
					PrintError("当前位置缺少运算符，如 \"*\" 或 \"+\"!", row, col);
				}
				else
				{
					char errorMsg[20]; // 报错信息
					int shiftState;
					int shortTag;
					switch(action.i)
					{
					case 3:
						strcpy_s(errorMsg, "缺少\"=\"！");
						shiftState = 10;
						shortTag = Tag::EQUAL;
						break;
					case 4:
						strcpy_s(errorMsg, "缺少\",\"！");
						shiftState = 11;
						shortTag = Tag::COMMA;
						break;
					case 9:
						strcpy_s(errorMsg, "缺少\"+\"！");
						shiftState = 17;
						shortTag = Tag::PLUS;
						break;
					case 10:
						strcpy_s(errorMsg, "缺少\"*\"！");
						shiftState = 18;
						shortTag = Tag::MULT;
						break;
					case 11:
						strcpy_s(errorMsg, "缺少\")\"！");
						shiftState = 22;
						shortTag = Tag::RB;
						break;
					}
					s_state.Push(shiftState);
					s_token.Push(shortTag);
					s_seman.Push(shortTag);
					PrintError(errorMsg, row, col);
				}
			}
		}
	}

	// 关闭文件
	infile.close();
	return g_errorNum;
}


/**
	返回一个新的临时变量
*/
int NewTemp()
{
	char new_s[12] = "_T";
	char temp[12];
	IntToString(++g_tempIndex, temp);
	strcat_s(new_s, temp);

	return g_idTable.addId(new_s);
}
/**
	声明打印四元式
*/
void PrintEmit(char *op, char *arg1, char *arg2, char *result)
{
	cout << "\t{ (" << op << ", " << arg1 << ", " 
		<< arg2 << ", " << result << ") }";
}

/**
	声明错误信息
*/
void PrintError(const char *errorMsg, const int &row, const int &col)
{
	cerr << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	cerr << "┃ Error("<< row << ","<< col << ")! " << errorMsg << endl;
	cerr << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
}

/* //test lexical
	int row = 1;
	int col = 0;
	Token token(-1, row, col);
		cout << "test lexical :"  << endl;
	while(scan(infile, token, row, col) != EOF)
	{
		if(token.tag != 9)
		{
			printf("(%s,_)\n", Tag::words[token.tag]);
		}
		else
		{
			printf("(%s,%d)\n",Tag::words[token.tag], g_idTable.idTableIndex);
		}
	}*/
