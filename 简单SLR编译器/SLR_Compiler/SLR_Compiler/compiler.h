/*
compiler.h: �����������ڱ��빤���ĺ���,���
*/
#ifndef COMPILER_H
#define COMPILER_H


#include "util.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/**
	Tag�ࣺ �����˸����ʷ���Ԫ��Ӧ�ĳ���
*/
class Tag
{
public:
	// �ս��
	static const int INT = 0, FLOAT = 1, ID = 2, // int float id
		PLUS = 3, MULT = 4, EQUAL = 5, LB = 6,  // + * = (
		RB = 7, COMMA = 8, SEMICOLON = 9 ; // ) , ;
		

	// ���ս�� ����ȥ10000��Ϊ nonts ����Ӧ��������Ϊ�����ս������ս����
	static const int L = 10000, S = 10001, A = 10002,
		D = 10003, E = 10004, T = 10005, F = 10006;

	// �ս������Ӧ�� string
	static char *words[10];

	// ���ս������Ӧ�� string
	static char *nonts[7];
};



/**
	Token�ࣺ Ϊ�ʷ���Ԫ
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
	�����ʶ�������ݽṹ
*/
typedef struct Identifier
{
	char name[32];
	char type[32];
	int addr;
} Identifier;

/**
	�������ʽ�����ݽṹ
*/
typedef struct Production
{
	int head; // ����ʽͷ�����󲿣�
	int tail[3]; // ����ʽβ�����Ҳ�����������Ϊ3
	int length; // ����ʽβ������
} Production;

// 
void PrintProduction(const Production &pro);

/**
	Action������ݽṹ
*/
typedef struct Action
{
	// ��Ƕ�������
	char a; // s���ƽ���r����Լ��a�����գ�e������

	// ���嶯��������
	int i;
} Action;

// �����������Ļ
void PrintAction(const Action &action);

/**
	�ֶ���ʼ�� Action��
*/
void initActions(Action actions[23][10]);


/**
	Goto ������ݽṹ
*/
typedef struct Goto
{
	int cs; // ��ǰ״̬
	int i;  // ���ս������
	int ss; // Ҫ�ƽ���״̬��
} Goto;

// 
int FindGoto(int &cs, int &i, Goto gotos[12]);


/**
	�ֶ���ʼ�� Goto��
*/
void initGotos(Goto gotos[]);


/**
	�﷨���������������������
*/
int parse(const char *filePath);

/**
	�ʷ�������ÿ�η���һ���ʷ���Ԫ
*/
int scan(ifstream &infile, Token &token, int &row, int &col);



/**
	Token�ࣺ Ϊ�ʷ���Ԫ
*/
class IdTable
{
public:
	Identifier idTable[100]; // ��С����Ϊ100
	int idTableSize;
	int idTableIndex; // ��ǰid�ڱ�ʶ�����е�����

	// ��ʼ����ʶ����
	IdTable()
	{	idTableSize = 0; idTableIndex = 0;	}

	/**
		���ݱ�ʶ����Ѱ��Id
	*/
	int findId(const char *id);

	/**
		�����ʶ��
	*/
	int addId(const char *id);


};


/**
	������ʾջ��Ϣ�ĺ�����״̬ջ������ջ��
*/
void ShowStacks(Stack<int> &s_state, Stack<int> &s_token);

#endif
