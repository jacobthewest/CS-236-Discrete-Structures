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

	//Send the file to the scanner
	Lexer lexerObj(argv[1]);

	//We have now broken out of the while loop and processed everything so far. We are going to print the token vector now.
	cout << lexerObj.printFromScannerClass();
	//system("pause");
	return 0;
}

//int main(int argc, char* argv[]) {
//	try {
//		Lexer lexerObject = new Lex(argv[1]);
//		DatalogProgram datalogProgram =	new DatalogProgram(lexerObject);
//		cout << “Success!” << endl;
//		datalogProgram.print();
//	}
//	catch (Token token) {
//		cout << “Failure!” << endl;
//		cout << token.toString() << endl;
//	}
//}


//Create a Parser class
//	Takes a vector of Token objects
//	Checks the syntax
//	Run this to see if you get "Success!" or "Failure!" appropriately for the tests on the website
//Create the DatalogProgram, Predicate, Rule, and Parameter classes
//	Make sure you understand what makes up each of these classes
//	Look at the input and output of the examples on the website
//Modify your Parser to create instances of the wrapper classes
//	Test your code against the example tests on the website
