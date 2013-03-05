/*
	util.cpp: 实现util.h中声明的数据结构和方法
*/

#include "util.h"
#include <iostream>
using namespace std;



/**
	判断是否为字母
*/
bool isLetter(const char &ch)
{
	if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		return true;
	}
	return false;
}

/**
	判断是否为字母或数字
*/
bool isLetterOrDigit(const char &ch)
{
	if(ch >= '0' && ch <= '9' || isLetter(ch))
	{
		return true;
	}
	return false;
}


/**
	把整形转化为字符串数组
*/
void IntToString(int inte, char new_s[10])
{
	char temp[10];
	int i;
	for(i = 0; inte > 0; i++)
	{
		temp[i] = '0' + (inte % 10);
		inte /= 10;
	}
	temp[i] = '\0';
	int j = strlen(temp) - 1;
	for(i = 0; j >= 0; j--,i++)
	{
		new_s[i] = temp[j];
	}
	new_s[i] = '\0';
}