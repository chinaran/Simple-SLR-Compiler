/*
compiler.h: 用于声明关于编译工作的函数,类等
*/
#ifndef COMPILER_H
#define COMPILER_H


#include "util.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/**
	Tag类： 定义了各个词法单元对应的常量
*/
class Tag
{
public:
	// 终结符
	static const int INT = 0, FLOAT = 1, ID = 2, // int float id
		PLUS = 3, MULT = 4, EQUAL = 5, LB = 6,  // + * = (
		RB = 7, COMMA = 8, SEMICOLON = 9 ; // ) , ;
		

	// 非终结符 （减去10000即为 nonts 所对应的索引，为区分终结符与非终结符）
	static const int L = 10000, S = 10001, A = 10002,
		D = 10003, E = 10004, T = 10005, F = 10006;

	// 终结符所对应的 string
	static char *words[10];

	// 非终结符所对应的 string
	static char *nonts[7];
};



/**
	Token类： 为词法单元
*/
class Token
{
public:
	int tag;
	int row;
	int col;
	Token(int t,int r, int c):tag(t), row(r), col(c){}
	void setAll(int t,int r, int c)
	{	tag = t; row = r; col = c;	};
};


/**
	定义标识符的数据结构
*/
typedef struct Identifier
{
	char name[32];
	char type[32];
	int addr;
} Identifier;

/**
	定义产生式的数据结构
*/
typedef struct Production
{
	int head; // 产生式头部（左部）
	int tail[3]; // 产生式尾部（右部），长度暂为3
	int length; // 产生式尾部长度
} Production;

// 
void PrintProduction(const Production &pro);

/**
	Action表的数据结构
*/
typedef struct Action
{
	// 标记动作类型
	char a; // s：移进，r：规约，a：接收，e：错误。

	// 具体动作的索引
	int i;
} Action;

// 输出动作到屏幕
void PrintAction(const Action &action);

/**
	手动初始化 Action表
*/
void initActions(Action actions[23][10]);


/**
	Goto 表的数据结构
*/
typedef struct Goto
{
	int cs; // 当前状态
	int i;  // 非终结符索引
	int ss; // 要移进的状态号
} Goto;

// 
int FindGoto(int &cs, int &i, Goto gotos[12]);


/**
	手动初始化 Goto表
*/
void initGotos(Goto gotos[]);


/**
	语法分析和语义分析的主函数
*/
int parse(const char *filePath);

/**
	词法分析，每次返回一个词法单元
*/
int scan(ifstream &infile, Token &token, int &row, int &col);



/**
	Token类： 为词法单元
*/
class IdTable
{
public:
	Identifier idTable[100]; // 大小暂设为100
	int idTableSize;
	int idTableIndex; // 当前id在标识符表中的索引

	// 初始化标识符表
	IdTable()
	{	idTableSize = 0; idTableIndex = 0;	}

	/**
		根据标识符，寻找Id
	*/
	int findId(const char *id);

	/**
		插入标识符
	*/
	int addId(const char *id);


};


/**
	声明显示栈信息的函数（状态栈，符号栈）
*/
void ShowStacks(Stack<int> &s_state, Stack<int> &s_token);

#endif
