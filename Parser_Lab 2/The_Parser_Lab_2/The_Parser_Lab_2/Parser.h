#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

using namespace std;

class Parser {
private:
	unsigned int index_m;
	vector<Token*> tokenListCopyForParserClass_m;
	Token* currentToken;
	DatalogProgram datalogProgramObject;
	Predicate predicateObject;
	Rule ruleObject;
	string expressionString_m;
	size_t trackingNum_m;
public:
	//Constructor
	Parser() {};
	Parser(vector<Token*> tokenList);
	~Parser() {};

	DatalogProgram getDatalogProgramObject() { return datalogProgramObject; }
	void parseDatalogProgram();
	bool match(TokenType tokenType);
	void parseSchemeList();
	void parseFactList();
	void parseRuleList();
	void parseQueryList();
	void parseScheme();
	void parseFact();
	void parseRule();
	void parseQuery(); 
	void parseHeadPredicate();
	void parsePredicate();
	void parsePredicateList();
	void parseParameterList();
	void parseStringList();	
	void parseIdList();
	void parseParameter();
	void parseParameter(bool& doNotPrintBecauseOfExpression, string& expressionString_m, size_t& trackingNum_m);
	void parseExpression(string& expressionString_m, size_t& trackingNum_m); 
	void parseOperator(string& expressionString_m);
	void parseId(ostringstream &expressionOss);
};
#endif //PARSER_H