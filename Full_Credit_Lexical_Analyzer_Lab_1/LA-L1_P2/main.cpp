/**********************
Jacob West
Lexical Analyzer
CS 236 Section 3
jacobthewest@gmail.com
**********************/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Lexer.h"
#include "Scanner.h"
#include "Token.h"

//Check for memory leaks
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK    ;

#endif

int main(int argc, char * argv[])
{
	VS_MEM_CHECK;

	if (argc < 2)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	//cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}

	//Send file to lexer
	Lexer lexerObject(argv[1]);

	//We have now broken out of the while loop and processed everything so far. We are going to print the token vector now.
	cout << lexerObject.printTheVectorOfTokenPointers();
	//system("pause");
	return 0;
}