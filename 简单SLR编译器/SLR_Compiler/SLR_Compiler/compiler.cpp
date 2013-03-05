/*
	compiler.cpp: ����ʵ�ִ󲿷�compiler.h�е��෽��
*/

#include "compiler.h"
#include "util.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

int testv = 3;

// ��ʼ�� words �ĳ�ֵ
char* Tag::words[10] = {"int", "float", "id", "+", "*", "=", "(", ")", ",", ";"};
// ��ʼ�� nonts �ĳ�ֵ
char* Tag::nonts[7] = {"L", "S", "A", "D", "E", "T", "F"};

/**
	���ݱ�ʶ����Ѱ��Id
	����ֵ��
		-1			�� ������
		idTableIndex�� ����
*/
int IdTable::findId(const char *id)
{
	for(int i = 0; i < idTableSize; i++)
	{
		if(!strcmp(id, idTable[i].name))
		{
			idTableIndex = i;
			return i;
		}
	}
	return -1;
}

/**
	�����ʶ��
	����ֵ��
		idTableIndex
*/
int IdTable::addId(const char *id)
{
	idTableIndex = findId(id);
	// �����ʶ��������id�������
	if(idTableIndex == -1)
	{
		idTableIndex = idTableSize;
		strcpy_s(idTable[idTableSize++].name, id);
	}
	return idTableIndex;
}

/**
	�ֶ���ʼ�� Goto��
*/
void initGotos(Goto gotos[])
{

}


/**
	�ֶ���ʼ�� Action��
	// ��ʱ��ȫ�ֱ�������Ҫ����д���ٰ���
*/
void initActions(Action actions[23][10])
{
	//actions[0][0] = {'s', 3};
}


/**
	��ӡһ������ʽ����Ļ
*/
void PrintProduction(const Production &pro)
{
	cout << Tag::nonts[pro.head - 10000] << " �� ";
	for(int i = 0; i < pro.length; i++)
	{
		if(pro.tail[i] >= 10000)
		{	// Ϊ���ս��ʱ
			cout << Tag::nonts[pro.tail[i] - 10000] << " ";
		}
		else
		{	// Ϊ�ս��ʱ
			cout << Tag::words[pro.tail[i]] << " ";
		}
	}
}

/**
	�����������Ļ
*/
void PrintAction(const Action &action)
{
	cout << action.a << action.i;
}

void ShowStacks(Stack<int> &s_state, Stack<int> &s_token)
{
	// print s_state
	int s_length = s_state.Length();
	for(int i = 0; i < s_length; i++)
	{
		printf("%2d ",s_state.Get(i));
	}
	int tab = (4*8 - 3*s_length) / 8;
	if((4*8 - 3*s_length) % 8 != 0)
	{
		tab++;
	}
	for(int i = 0; i < tab; i++)
	{
		printf("\t");
	}

	// print s_token
	int charNum = 0;
	for(int i = 0; i < s_length; i++)
	{
		int index = s_token.Get(i);
		if(index >= 10000)
		{
			printf("%s ", Tag::nonts[index-10000]);
			charNum += strlen(Tag::nonts[index-10000]) + 1;
		}
		else
		{
			printf("%s ", Tag::words[index]);
			charNum += strlen(Tag::words[index]) + 1;
		}
	}
	tab = (3*8 - charNum) / 8;
	if((3*8 - charNum) % 8 != 0)
	{
		tab++;
	}
	for(int i = 0; i < tab; i++)
	{
		printf("\t");
	}
}

/**
	����ϵ������ gotos ��Ԫ��
*/
int FindGoto(int &cs, int &i, Goto gotos[12])
{
	for(int j = 0; j < 12; j++)
	{
		if(gotos[j].cs == cs && gotos[j].i == i)
		{
			return gotos[j].ss;
		}
	}
	return -1; // ���������Ӧ�ò��ᷢ��
}
