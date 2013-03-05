/*
lexical.cpp: ���дʷ�����

*/

#include "compiler.h"
#include "util.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

// ����ȫ�ֱ���
extern IdTable g_idTable;
extern int g_errorNum;

/**
	�ʷ�������ÿ�η���һ���ʷ���Ԫ
	������ ȫ��Ϊ����
		infile���ļ�������
		token���ʷ���Ԫ
		row����ǰ�ʷ���Ԫ����
		col����ǰ�ʷ���Ԫ����
	����ֵ��
		// -2�������Ƿ��ַ� rescan��֪���õ��Ϸ��ַ�
		-1���ļ�������EOF��
		0 ����������
		*/
int scan(ifstream &infile, Token &token, int &row, int &col)
{
	// ֱ������һ���Ϸ����ַ�
	// rescan: !!! goto���Ч��Ҫ��һЩ
	while(true)
	{
		char peek = infile.get();
		// ���� �ո� �Ʊ���� �ļ�������
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

		// �õ��ʷ���Ԫ
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

		// �õ��ؼ��֣���ʾ��
		char identifier[32]; // ��ʾ����󳤶�����Ϊ32
		if(isLetter(peek)) 
		{
			// �ѱ�ʾ����ؼ��ַŵ� identifier ��
			identifier[0] = peek;
			int i = 1;
			for(; isLetterOrDigit(infile.peek()); i++)
			{
				infile.get(identifier[i]);
				col++;
			}
			identifier[i] = '\0'; // string end
			// ʶ��ؼ���
			// Ӧ��дһ����������һ���ؼ��ֱ����ڳ���Ƚϼ�ª����͵����
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
			else // ʶ���ʶ��������ӵ���ʶ����
			{
				token.setAll(Tag::ID, row, col);
				g_idTable.addId(identifier);
			}
		}
		// �õ��Ƿ��ַ�
		else
		{
			// �����������Ļ
			cerr << "����������������������������������������������������������������������������������������" << endl;
			cerr << "�� Error("<< row << ","<< col << ")! ���ڷǷ��ַ��� \"" << peek << "\"" << endl;
			cerr << "����������������������������������������������������������������������������������������" << endl;
			g_errorNum++;
			//goto rescan;
			continue;
		}
		break;
	}
	return 0;
}

