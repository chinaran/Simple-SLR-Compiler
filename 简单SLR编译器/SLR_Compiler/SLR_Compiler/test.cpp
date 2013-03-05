/*
	justTest.cpp: just for debug and test
*/

#include "compiler.h"
#include "util.h"

#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

char Peek(ifstream &infile);
void OutputFile(const char *filePath);

extern Action g_actions[23][10];
extern Goto g_gotos[12];
extern Production pros[13];
extern IdTable g_idTable;
extern int NewTemp();

int test ()
{
	for(int i = 0; i < 50; i++)
		NewTemp();


	/*char new_s[10];
	IntToString(123, new_s);
	cout << new_s << endl;*/

	/*char s[32] = "china";
	char *s1 = s;
	cout << sizeof(s) << endl;
	cout << sizeof(s1) << endl;
	cout << sizeof(*s1) << endl;*/

	/*label:
	cout << g_idTable.idTableIndex << endl;
	goto label;*/

	/*for(int i = 0; i < 13; i++)
	{
		PrintProduction(pros[i]);
		cout << endl;
	}*/

	/*cout << "g_actions=" << g_actions[22][9].i << g_actions[22][9].i << endl;
	cout << "g_gotos=" << g_gotos[11].i << endl;*/

	/*Action action;
	action.a = 'a'; action.i = 0;
	cout << action.a << endl;
	cout << action.i << endl;*/

	//action = {'a' , 1};

	/*cout << Tag::words[0] << endl;*/


	/*char *words[] = {"int", "float", "=", "+", "*", "(", ")", ",", ";", "id"};
*/
	/*Tag::words = new */
	//Tag::words = new string[10];
	//Tag::words[0] = "sdfs";
	//cout << Tag::words[0] << endl;

	//Tag::words = {"int", "float", "=", "+", "*", "(", ")", ",", ";", "id"};
	//Tag::words = {"asdf"};
	/*char s[32];
	s[0] = 'i';
	s[1] = 'n';
	s[2] = 't';
	s[3] = '\0';
	cout << "sting = " << s << endl;
	cout << strcmp(s, "int") << endl;*/

	//cout << Tag::COMMA << endl;
	//OutputFile("test.slr");

	/*cout << "Can you feel me ?" << endl; 
	cout << "No" << endl;
	cerr << "Error !" << endl;*/



	return 0;
}


void OutputFile(const char *filePath)
{
	ifstream infile(filePath, ios::in);
	if(!infile)
	{
		cerr << "Sorry, can't open " << filePath << " !" << endl;
		exit(0);
	}
	while(!infile.eof())
	{
		cout.put(Peek(infile));
	}
	//cout << endl;

}

char Peek(ifstream &infile)
{
	return infile.get();
}