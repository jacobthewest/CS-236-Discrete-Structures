/**********************
Jacob West
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
#include "DatalogProgram.h"
#include "Database.h"
#include "Parser.h"

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

	Lexer lexerObj(argv[1]); //Send the file to the scanner
	vector<Token*> copyOfVectorOfTokenPointers = lexerObj.getTokenList();

	try {
		Parser parserObj(copyOfVectorOfTokenPointers);
		DatalogProgram datalogProgramObject = parserObj.getDatalogProgramObject();
		Database databaseObject(datalogProgramObject.getSchemes(), datalogProgramObject.getFacts(),
			datalogProgramObject.getRules(), datalogProgramObject.getQueries());
		databaseObject.evaluateRules();
		databaseObject.evaluateQueries();
	}
	catch (string offendingToken) { //Catches a string, not a token
		cout << "Failure!" << endl;
		cout << "  " << offendingToken;
	}

	system("pause");
	return 0;
}