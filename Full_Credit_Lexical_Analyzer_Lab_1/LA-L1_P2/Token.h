#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream> //ostringstream
using std::string;

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
	Token(TokenType type, string valueSoFar, unsigned int lineNumber);
	~Token() {};
	string tokenTypeToString(TokenType tt);
	string toString();
};
#endif	// TOKEN_H