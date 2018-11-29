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
	~Lexer() {};

	/* Keep complexity down 18 token types Instead of over a dozen if statements, use 1 switch case
	This function will turn what we have into a token and add it to our vector */


	/*Runs the program through all of the states based on the inputs*/
	void startTheProgram();
	string printFromScannerClass() { return scanner.printTheVectorOfTokenPointers(); }
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

	//Lab 2 Functions
	/*top() {
	
	}
	pop() {
	
	}
	getNextToken(TokenType tokenType) {
		Token result = top();
		Token resultType = result.getTokenType();
		if (resultType == EOF_TYPE || resultType != tokenType) {
			throw result;
	}*/

	//Lex
	//	Token getNextToken(TokenType tokenType) {
	//	Token result = top();
	//	Token resultType = result.getTokenType();
	//	if (resultType == EOF || resultType != tokenType) {
	//		throw result;
	//	}
	//	pop();
	//	return result;
	//}
};
#endif	// LEXER_H