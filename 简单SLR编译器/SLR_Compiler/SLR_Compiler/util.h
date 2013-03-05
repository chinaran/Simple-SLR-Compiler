/*
	util.h: ���ڴ�Ź�����͹�������
		    ��ջ�����ݽṹ
*/
#ifndef UTIL_H
#define UTIL_H


#include<iostream>
using namespace std;

// just test fun
int test();

/**
	�ж��Ƿ�Ϊ��ĸ
*/
bool isLetter(const char &ch);


/**
	�ж��Ƿ�Ϊ��ĸ������
*/
bool isLetterOrDigit(const char &ch);

/**
	������ת��Ϊ�ַ�������
*/
void IntToString(int inte, char new_s[10]);


/**
	����ջ�����ݽṹ��������ʵ��
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

	/*void Push(Type &e);*/ // �����԰ѳ�����ջ
	void Push(Type e); 

	Type & Pop();

	Type & Get(int index) {	return elem[index];	}

};

// ==================================================
// C++ģ��������Ͷ���������һ�������Ҿ���ʹ������ .h ����
// ==================================================


/**
	���� Stack �е�δʵ�ֵķ���
*/

template <typename Type>
Stack<Type>::Stack(int size):top(-1), maxSize(size)
{
	elem = new Type[maxSize];
	if(!elem)
	{
		cerr << "���ش����ڴ�Ϊջ����Type["<< maxSize<< "] ʧ�ܣ�" << endl;
		exit(0);
	}
}

template <typename Type>
Type & Stack<Type>::Peek()
{
	// ��ջ���գ�Peek���������򱨴�
	// ��һЩ����£�Ϊ����Ч�ʣ����Ժ��԰�ȫ����
	// ���·�����������������
	/*if(IsEmpty())
	{
		cerr << "ջ�գ����ɽ��� Peek������" << endl;
		exit(0);
	}*/
	return elem[top];
}

template <typename Type>
Type & Stack<Type>::Pop()
{
	/*if(IsEmpty())
	{
		cerr << "ջ�գ����ɽ��� Pop������" << endl;
		exit(0);
	}*/
	return elem[top--];
}

template <typename Type>
void Stack<Type>::Push(Type e)
{
	// ���ջ����ÿ�����ӵ�ǰջ������һ��
	/*if(IsFull())
	{
		int newSize = maxSize + maxSize / 2;
		Type *p = new Type[newSize];
		if(!p)
		{
			cerr << "���ش����ڴ�Ϊջ����Type["<< newSize<< "] ʧ�ܣ�" << endl;
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

	// ���ջû��
	elem[++top] = e;
}

#endif