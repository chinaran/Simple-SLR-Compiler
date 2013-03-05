/*
	util.cpp: ʵ��util.h�����������ݽṹ�ͷ���
*/

#include "util.h"
#include <iostream>
using namespace std;



/**
	�ж��Ƿ�Ϊ��ĸ
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
	�ж��Ƿ�Ϊ��ĸ������
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
	������ת��Ϊ�ַ�������
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