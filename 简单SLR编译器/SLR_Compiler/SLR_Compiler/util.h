/*
	util.h: 用于存放工具类和公共操作
		    如栈等数据结构
*/
#ifndef UTIL_H
#define UTIL_H


#include<iostream>
using namespace std;

// just test fun
int test();

/**
	判断是否为字母
*/
bool isLetter(const char &ch);


/**
	判断是否为字母或数字
*/
bool isLetterOrDigit(const char &ch);

/**
	把整形转化为字符串数组
*/
void IntToString(int inte, char new_s[10]);


/**
	声明栈的数据结构，用数组实现
*/

template <typename Type>
class Stack
{
private:
	int top;
	Type *elem;
	int maxSize;

public:
	Stack(int size);

	~Stack() {	delete []elem;	}

	bool IsEmpty() {	return (top == -1);	}

	bool IsFull() {	return (top == maxSize - 1);	}

	void Clear() {	top = -1;	}

	int Length() {	return (top + 1);	}

	int MaxSize() {	return maxSize;	}

	Type & Peek();

	/*void Push(Type &e);*/ // 不可以把常量入栈
	void Push(Type e); 

	Type & Pop();

	Type & Get(int index) {	return elem[index];	}

};

// ==================================================
// C++模板的声明和定义必须放在一起，所以我就忍痛都放在 .h 中了
// ==================================================


/**
	定义 Stack 中的未实现的方法
*/

template <typename Type>
Stack<Type>::Stack(int size):top(-1), maxSize(size)
{
	elem = new Type[maxSize];
	if(!elem)
	{
		cerr << "严重错误，内存为栈分配Type["<< maxSize<< "] 失败！" << endl;
		exit(0);
	}
}

template <typename Type>
Type & Stack<Type>::Peek()
{
	// 若栈不空，Peek操作，否则报错
	// 但一些情况下，为考虑效率，可以忽略安全处理
	// 以下方法均不包括错误检查
	/*if(IsEmpty())
	{
		cerr << "栈空，不可进行 Peek操作！" << endl;
		exit(0);
	}*/
	return elem[top];
}

template <typename Type>
Type & Stack<Type>::Pop()
{
	/*if(IsEmpty())
	{
		cerr << "栈空，不可进行 Pop操作！" << endl;
		exit(0);
	}*/
	return elem[top--];
}

template <typename Type>
void Stack<Type>::Push(Type e)
{
	// 如果栈满，每次增加当前栈容量的一半
	/*if(IsFull())
	{
		int newSize = maxSize + maxSize / 2;
		Type *p = new Type[newSize];
		if(!p)
		{
			cerr << "严重错误，内存为栈分配Type["<< newSize<< "] 失败！" << endl;
			exit(0);
		}
		for(int i = 0; i < maxSize; i++)
		{
			p[i] = elem[i];
		}
		delete []elem;
		elem = p;
		p = NULL;
		maxSize = newSize;
	}*/

	// 如果栈没满
	elem[++top] = e;
}

#endif