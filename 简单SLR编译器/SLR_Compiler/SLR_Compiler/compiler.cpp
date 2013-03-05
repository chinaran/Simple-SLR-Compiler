/*
	compiler.cpp: 用于实现大部分compiler.h中的类方法
*/

#include "compiler.h"
#include "util.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

int testv = 3;

// 初始化 words 的初值
char* Tag::words[10] = {"int", "float", "id", "+", "*", "=", "(", ")", ",", ";"};
// 初始化 nonts 的初值
char* Tag::nonts[7] = {"L", "S", "A", "D", "E", "T", "F"};

/**
	根据标识符，寻找Id
	返回值：
		-1			： 不存在
		idTableIndex： 存在
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
	插入标识符
	返回值：
		idTableIndex
*/
int IdTable::addId(const char *id)
{
	idTableIndex = findId(id);
	// 如果标识符表不存在id，则插入
	if(idTableIndex == -1)
	{
		idTableIndex = idTableSize;
		strcpy_s(idTable[idTableSize++].name, id);
	}
	return idTableIndex;
}

/**
	手动初始化 Goto表
*/
void initGotos(Goto gotos[])
{

}


/**
	手动初始化 Action表
	// 暂时用全局变量做，要不得写多少啊！
*/
void initActions(Action actions[23][10])
{
	//actions[0][0] = {'s', 3};
}


/**
	打印一条产生式到屏幕
*/
void PrintProduction(const Production &pro)
{
	cout << Tag::nonts[pro.head - 10000] << " → ";
	for(int i = 0; i < pro.length; i++)
	{
		if(pro.tail[i] >= 10000)
		{	// 为非终结符时
			cout << Tag::nonts[pro.tail[i] - 10000] << " ";
		}
		else
		{	// 为终结符时
			cout << Tag::words[pro.tail[i]] << " ";
		}
	}
}

/**
	输出动作到屏幕
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
	返回系数矩阵 gotos 的元素
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
	return -1; // 错误情况，应该不会发生
}
