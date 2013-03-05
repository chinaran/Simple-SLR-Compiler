/*
lexical.cpp: 进行词法分析

*/

#include "compiler.h"
#include "util.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

// 引入全局变量
extern IdTable g_idTable;
extern int g_errorNum;

/**
	词法分析，每次返回一个词法单元
	参数： 全部为引用
		infile：文件输入流
		token：词法单元
		row：当前词法单元行数
		col：当前词法单元列数
	返回值：
		// -2：报错，非法字符 rescan，知道得到合法字符
		-1：文件结束（EOF）
		0 ：正常结束
		*/
int scan(ifstream &infile, Token &token, int &row, int &col)
{
	// 直到返回一个合法的字符
	// rescan: !!! goto语句效率要低一些
	while(true)
	{
		char peek = infile.get();
		// 过滤 空格， 制表符， 文件结束符
		for( ; ; peek = infile.get())
		{	
			if(peek == ' ' || peek == '\t')
			{
				col++;
			}
			else if (peek == '\n')
			{
				row++;
				col = 0;
			}
			else if (peek == EOF)
			{
				return EOF;
			}
			else
			{
				col++;
				break;
			}
		}

		// 得到词法单元
		switch(peek)
		{
		case '=' :
			token.setAll(Tag::EQUAL, row, col);
			return 0; 
		case '+' :
			token.setAll(Tag::PLUS, row, col);
			return 0; 
		case '*' :
			token.setAll(Tag::MULT, row, col);
			return 0; 
		case '(' :
			token.setAll(Tag::LB, row, col);
			return 0; 
		case ')' :
			token.setAll(Tag::RB, row, col);
			return 0; 
		case ',' :
			token.setAll(Tag::COMMA, row, col);
			return 0; 
		case ';' :
			token.setAll(Tag::SEMICOLON, row, col);
			return 0; 
		default:
			break;
		}

		// 得到关键字，标示符
		char identifier[32]; // 标示符最大长度暂设为32
		if(isLetter(peek)) 
		{
			// 把标示符或关键字放到 identifier 中
			identifier[0] = peek;
			int i = 1;
			for(; isLetterOrDigit(infile.peek()); i++)
			{
				infile.get(identifier[i]);
				col++;
			}
			identifier[i] = '\0'; // string end
			// 识别关键字
			// 应该写一个函数，建一个关键字表，鉴于程序比较简陋，就偷懒了
			if(!strcmp(identifier, "int"))
			{
				token.setAll(Tag::INT, row, col);
				return 0;
			}
			else if(!strcmp(identifier, "float"))
			{
				token.setAll(Tag::FLOAT, row, col);
				return 0;
			}
			else // 识别标识符，并添加到标识符表
			{
				token.setAll(Tag::ID, row, col);
				g_idTable.addId(identifier);
			}
		}
		// 得到非法字符
		else
		{
			// 报错，输出到屏幕
			cerr << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
			cerr << "┃ Error("<< row << ","<< col << ")! 存在非法字符： \"" << peek << "\"" << endl;
			cerr << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
			g_errorNum++;
			//goto rescan;
			continue;
		}
		break;
	}
	return 0;
}

