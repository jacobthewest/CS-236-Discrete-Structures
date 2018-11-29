#pragma once
//Point of this class is to sort chars into tokens
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream> //std::ifstream
#include <sstream> //ostringstream

#include "Token.h"
#include "Scanner.h"

using std::string;

enum States {
	START_STATE, COLON_DASH_STATE, SINGLE_CHARACTER_STATE, STRING_START_STATE, STRING_END_STATE, SINGLE_LINE_COMMENT_STATE,
	MULTI_LINE_COMMENT_STATE, UNDEFINED_STATE, ID_STATE, END_OF_FILE_STATE, WHITESPACE_STATE
};	

class Lexer {
private:
	std::vector<Token*> tokenList;
	Scanner scanner;
	States currentState;
	string valueSoFar; //Used to build a string to instantiate a new token
	bool endOfProgram_NowWePrint_m;
public:
	//Constructor that takes the file name as a string and creates the ifstream object
	Lexer(string fileName);
	~Lexer() { deallocateMemory(); };

	/* Keep complexity down 18 token types Instead of over a dozen if statements, use 1 switch case
	This function will turn what we have into a token and add it to our vector */
	void tokenize();
	void tokenize(unsigned int stringStartedOnThisLineNumber);


	//Deallocate's memory stored in the vector of token pointers
	void deallocateMemory();

	/*Runs the program through all of the states based on the inputs*/
	void startTheProgram();

	//Print by going to vector, and toString for each index
	string printTheVectorOfTokenPointers();
	void startState();
	void singleCharacterState();
	void colonDashState();
	void stringStartState();
	void stringEndState();
	void singleLineCommentState();
	void multiLineCommentState();
	void undefinedState();
	void idState();
	void endOfFileState();
	void whitespaceState();
	void setKeywordType(string valueSoFar);
	void endOfMultiLineCommentOrEndOfFileIsTrue();
};
#endif	// LEXER_H