#include "Token.h"

using namespace std;

//Constructor for token object
Token::Token(TokenType type, string valueSoFar, unsigned int lineNumber) {
	this->value_m = valueSoFar;
	this->lineNumber_m = lineNumber;
	this->type_m = type;
}

//Print each individual token
string Token::toString() {
	ostringstream oss;
	oss << "(" << tokenTypeToString(this->type_m) << ",\"" << this->value_m << "\"," << this->lineNumber_m << ")";
	return oss.str();
}

//Converts the tokenType to a printable string format
string Token::tokenTypeToString(TokenType tt) {
	switch (tt) {
	case COMMA: return "COMMA"; break;
	case PERIOD: return "PERIOD"; break;
	case Q_MARK: return "Q_MARK"; break;
	case LEFT_PAREN: return "LEFT_PAREN"; break;
	case RIGHT_PAREN: return "RIGHT_PAREN"; break;
	case COLON: return "COLON"; break;
	case COLON_DASH: return "COLON_DASH"; break;
	case MULTIPLY: return "MULTIPLY"; break;
	case ADD: return "ADD"; break;
	case SCHEMES: return "SCHEMES"; break;
	case FACTS: return "FACTS"; break;
	case RULES: return "RULES"; break;
	case QUERIES: return "QUERIES"; break;
	case ID: return "ID"; break;
	case STRING: return "STRING"; break;
	case COMMENT: return "COMMENT"; break;
	case WHITESPACE: return "WHITESPACE"; break;
	case UNDEFINED: return "UNDEFINED"; break;
	case EOF_TYPE: return "EOF"; break;
	default: return "There was an error, your token type was not recognized in the TokenTypeToString(TokenType tt) function in the Token.cpp file";
		break;
	}
}