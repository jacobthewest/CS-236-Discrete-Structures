#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <sstream> //ostringstream

using namespace std;

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, ERROR,
	SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, EOF_TYPE
};

class Token {
private:
	string value_m;
	unsigned int lineNumber_m;
	TokenType type_m;

public:
	//Token constructor
	Token(TokenType type, std::string valueSoFar, unsigned int lineNumber);
	~Token() {};
	string tokenTypeToString(TokenType tt);
	string toString();
	TokenType getTokenType() { return type_m; }
	string getTokenTypeAsString(Token token);
	string getValue() { return value_m; }
};
#endif	// TOKEN_H