/**
	用于初始化 Action和 Goto表 及产生式
*/

#include "compiler.h"


// 声明与定义全局 产生式数组
Production pros[13] = 
{
	{Tag::L, {Tag::S}, 1},
	{Tag::S, {Tag::D}, 1},
	{Tag::S, {Tag::A}, 1},
	{Tag::D, {Tag::INT, Tag::ID}, 2},
	{Tag::D, {Tag::FLOAT, Tag::ID}, 2},
	{Tag::D, {Tag::D, Tag::COMMA, Tag::ID}, 3},
	{Tag::A, {Tag::ID, Tag::EQUAL, Tag::E}, 3},
	{Tag::E, {Tag::E, Tag::PLUS, Tag::T}, 3},
	{Tag::E, {Tag::T}, 1},
	{Tag::T, {Tag::T, Tag::MULT, Tag::F}, 3},
	{Tag::T, {Tag::F}, 1},
	{Tag::F, {Tag::LB, Tag::E, Tag::RB}, 3},
	{Tag::F, {Tag::ID}, 1}
};


// 声明与定义全局 Goto表
Goto g_gotos[12] = 
{
	{10, Tag::F, 14}, {15, Tag::F, 14}, {17, Tag::F, 14}, {18, Tag::F, 21},
	{10, Tag::T, 13}, {15, Tag::T, 13}, {17, Tag::T, 20}, {0, Tag::D, 6},
	{10, Tag::E, 12}, {15, Tag::E, 19}, {0, Tag::A, 2}, {0, Tag::S, 1}
};  


// 声明与定义全局 Action表
// 错误类型
// e0, e1:	当前符号多余
// e2 :	右括号不匹配[)]
// e3 :	(移进时)缺少等号[=]
// e4 :	(移进时)缺少逗号[,]
// e5, e6, e7, e8:	移进时）缺少标识符[id]
// e9 :	(移进时)缺少加号[+]
// e10:	(移进时)缺少乘号[*]
// e11:	(移进时)缺少左括号[(]
// e12:	(规约时)缺少分号[;]
// e13:	(规约时)缺少逗号[,]
// e14:	(规约时)缺少运算符[+，*]

Action g_actions[23][10] = 
{	
	{	// int      float      id        +         *          =         (         )         ,         ; 
/*0*/	{'s', 3}, {'s', 4}, {'s', 5}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'e', 1}, {'e', 1}
	},
	{
/*1*/	{'e', 0}, {'e', 0}, {'e', 12},{'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'a', -1}
	},
	{
/*2*/	{'e', 0}, {'e', 0}, {'e', 12},{'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'r', 2}
	},
	{
/*3*/	{'e', 1}, {'e', 1}, {'s', 8}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'e', 1}, {'e', 5}
	},
	{
/*4*/	{'e', 1}, {'e', 1}, {'s', 9}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'e', 1}, {'e', 6}
	},
	{
/*5*/	{'e', 1}, {'e', 1}, {'e', 3}, {'e', 1}, {'e', 1}, {'s', 10},{'e', 3}, {'e', 2}, {'e', 1}, {'e', 1}
	},
	{
/*6*/	{'e', 1}, {'e', 1}, {'e', 4}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'s', 7}, {'r', 1}
	},
	{
/*7*/	{'e', 1}, {'e', 1}, {'s', 11},{'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'e', 1}, {'e', 7}
	},
	{
/*8*/	{'e', 0}, {'e', 0}, {'e', 13},{'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'r', 3}, {'r', 3}
	},
	{
/*9*/	{'e', 0}, {'e', 0}, {'e', 13},{'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'r', 4}, {'r', 4}
	},
	{	// int      float      id        +         *          =         (         )         ,         ; 
/*10*/	{'e', 1}, {'e', 1}, {'s', 16},{'e', 1}, {'e', 8}, {'e', 1}, {'s', 15},{'e', 2}, {'e', 1}, {'e', 8}
	},
	{
/*11*/	{'e', 0}, {'e', 0}, {'e', 12},{'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'e', 0}, {'r', 5}, {'r', 5}
	},
	{
/*12*/	{'e', 1}, {'e', 1}, {'e', 9}, {'s', 17},{'e', 1}, {'e', 1}, {'e', 9}, {'e', 2}, {'e', 1}, {'r', 6}
	},
	{
/*13*/	{'e', 1}, {'e', 1}, {'e', 10},{'r', 8}, {'s', 18},{'e', 1}, {'e', 10},{'r', 8}, {'e', 2}, {'r', 8}
	},
	{
/*14*/	{'e', 0}, {'e', 0}, {'e', 14},{'r', 10},{'r', 10},{'e', 0}, {'e', 14},{'r', 10},{'e', 0}, {'r', 10}
	},
	{
/*15*/	{'e', 1}, {'e', 1}, {'s', 16},{'e', 1}, {'e', 1}, {'e', 1}, {'e', 1}, {'e', 2}, {'e', 1}, {'e', 8}
	},
	{	// int      float      id        +         *          =         (         )         ,         ; 
/*16*/	{'e', 0}, {'e', 0}, {'e', 14},{'r', 12},{'r', 12},{'e', 0}, {'e', 14},{'r', 12},{'e', 0}, {'r', 12}
	},
	{
/*17*/	{'e', 1}, {'e', 1}, {'s', 16},{'e', 1}, {'e', 8}, {'e', 1}, {'s', 15},{'e', 2}, {'e', 1}, {'e', 1}
	},
	{
/*18*/	{'e', 1}, {'e', 1}, {'s', 16},{'e', 1}, {'e', 1}, {'e', 1}, {'s', 15},{'e', 2}, {'e', 1}, {'e', 8}
	},
	{	// int      float      id        +         *          =         (         )         ,         ; 
/*19*/	{'e', 1}, {'e', 1}, {'e', 9}, {'s', 17},{'e', 1}, {'e', 1}, {'e', 9}, {'s', 22},{'e', 1}, {'e', 11}
	},
	{
/*20*/	{'e', 1}, {'e', 1}, {'e', 10},{'r', 7}, {'s', 18},{'e', 7}, {'e', 10},{'r', 7}, {'e', 1}, {'r', 7}
	},
	{
/*21*/	{'e', 12},{'e', 12},{'e', 12},{'r', 9}, {'r', 9}, {'e', 0}, {'e', 0}, {'r', 9}, {'e', 0}, {'r', 9}
	},
	{
/*22*/	{'e', 12},{'e', 12},{'e', 12},{'r', 11},{'r', 11},{'e', 0}, {'e', 0}, {'r', 11}, {'e', 0},{'r', 11}
	}
};