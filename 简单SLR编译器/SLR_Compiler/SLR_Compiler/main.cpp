/*
	main.cpp: 主调函数
			  由她调用相应函数，完成简单编译任务
	// test: slrc test.slr
*/

#include "util.h"
#include "compiler.h"
#include <sys\timeb.h>
#include <iostream>
using namespace std;

// 定义全局 标识符表 
IdTable g_idTable;

int main(int argc, char **argv)
{
	 //just test 
	//test();
	

	
	// 显示欢迎界面
	printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf("★                                                   ☆☆☆☆☆☆☆☆\n");
	printf("★    欢迎使用简单 SLR 编译器                      ☆                ☆      I will\n");
	printf("★    作者: Randy                                ☆     ☆☆☆        ☆      be\n");
	printf("★    版本: V 1.2（非长期支持！）                ☆    ☆★★ ☆       ☆    your \n");
	printf("★    使用: 输入 \"slrc xxx.slr(file name)\"         ☆    ☆☆☆       ☆        eyes\n");
	printf("★                                                   ☆☆☆☆☆☆☆☆☆\n");
	printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf(">\n>\n>");


	// 1. 读取要编译的文件
	//char *filePath = "test.slr"; // 为方便调试，先设为静态的
	char cmd[32];
	char filePath[64];
	cin >> cmd >> filePath;
	//cout << "cmd=" << cmd << "filePath=" << filePath << endl;
	if(strcmp(cmd, "slrc") != 0)
	{
		cout << ">\n>抱歉，该编译器暂不支持\"" << cmd << "\"命令!\n>" << endl;
		exit(0);
	}

	cout << ">\n>开始编译 [ " << filePath << " ]\n>\n>";

	// 获取编译开始的时间
	struct timeb tp_start;
	ftime(&tp_start);

	// 2. 进行语法语义分析
	int errorTime = parse(filePath);

	// 获取编译结束的时间
	struct timeb tp_end;
	ftime(&tp_end);

	// 编译共花费时间（ms）
	time_t ms_total = (tp_end.time - tp_start.time) * 1000 + (tp_end.millitm - tp_start.millitm);
	cout << ">\n>\n>\n>已用时间：" << ms_total << "ms" << endl;
	
	if(errorTime != 0)
	{
		cout << ">\n>错误个数: " << errorTime << endl;
		cout << ">编译失败 -_-!" << endl;
	}
	else
	{
		cout << ">\n>编译成功 ∩_∩~" << endl;
	}


	printf(">\n>");
	return 0;
}