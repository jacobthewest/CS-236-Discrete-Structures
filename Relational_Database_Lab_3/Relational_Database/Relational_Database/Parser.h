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
	void parseExpression();
	void parseOperator(ostringstream &expressionOss);
	void parseId(ostringstream &expressionOss);
};
#endif //PARSER_H