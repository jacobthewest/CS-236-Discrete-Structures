#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

#include <string>
#include <fstream>
using std::string;

class Scanner
{
private:
	std::ifstream fileStream_m;
	char currentChar_m;
	TokenType currentType_m;
	unsigned int currentLineNum_m = 1;
	unsigned int charLocation_m = 0;
	unsigned int stringStartedOnThisLineNumber_m = 0;
	bool firstTimeInStringStartState_m = true;
public:
	//Constructor
	Scanner() {};
	~Scanner() {};

	char advance();
	char peek() { return fileStream_m.peek(); }
	char getCurrentChar() { return currentChar_m; }
	TokenType getCurrentTokenType() { return currentType_m; }
	void openFile(string fileName);
	void incrementLineNumber() { currentLineNum_m++; }
	void decrementLineNumber() { currentLineNum_m--; }
	unsigned int getCurrentLineNumber() { return currentLineNum_m; }
	unsigned int getStringStartedOnThisLineNumber() { return stringStartedOnThisLineNumber_m; }
	void setCurrentTypeForSingleCharacter(char singleCharacter);
	void setCurrentTypeColonDash() { currentType_m = COLON_DASH; }
	void setCurrentTypeToSchemes() { currentType_m = SCHEMES; }
	void setCurrentTypeToFacts() { currentType_m = FACTS; }
	void setCurrentTypeToRules() { currentType_m = RULES; }
	void setCurrentTypeToQueries() { currentType_m = QUERIES; }
	void setCurrentTypeToID() { currentType_m = ID; }
	void setCurrentTypeToString() { currentType_m = STRING; }
	void setCurrentTypeToComment() { currentType_m = COMMENT; }
	void setCurrentTypeToWhitespace() { currentType_m = WHITESPACE; }
	void setCurrentTypeToUndefined() { currentType_m = UNDEFINED; }
	void setCurrentTypeToEndOfFile() { currentType_m = EOF_TYPE; }
	void setStringStartedOnThisLineNumber(unsigned int lineNumber) { stringStartedOnThisLineNumber_m = lineNumber; }
	bool checkIfActualKeyword(string& valueSoFar);
	bool checkIfCurrentCharIsCompatibleWithIDState(char characterToCheck);
	void setfirstTimeInStringStartStateBool(bool value) { firstTimeInStringStartState_m = value; }
	bool getFirstTimeInStringStartStateBool() { return firstTimeInStringStartState_m; }
};
#endif	// SCANNER_H