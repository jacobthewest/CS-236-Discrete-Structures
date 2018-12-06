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


	/* THIS IS THE GRAMMAR
		datalogProgram	->	SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
		        QUERIES COLON query queryList

		schemeList	->	scheme schemeList | lambda
		factList	->	fact factList | lambda
		ruleList	->	rule ruleList | lambda
		queryList	->	query queryList | lambda

		scheme   	-> 	headPredicate
		fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
		rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
		query	        ->      predicate Q_MARK

		headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
		predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	
		predicateList	->	COMMA predicate predicateList | lambda
		parameterList	-> 	COMMA parameter parameterList | lambda
		stringList	-> 	COMMA STRING stringList | lambda
		idList  	-> 	COMMA ID idList | lambda

		parameter	->	STRING
		parameter	->	ID
		parameter	->	expression
	
		expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
		operator	->	ADD | MULTIPLY
	*/

};

//TA Slides
//Take the vector<Token> in its contructor
//Must keep track of where in the vector it is at in the parsing process
//	int index
//Create a function to start the parsing
//	void parse();

//WHERE TO START
//Takes a vector of Token objects
//Checks the syntax
//Run this to see if you get "Success!" or "Failure!" appropriately for the tests on the website



//Now that you've made structures to hold the file's data, we need to change the Parser to make instances of them
//Good solution : make each function for a production in the grammar return what it is syntactically checking for (pseudo - constructors)
//parseSchemeList() returns vector<Predicate>
//parseHeadPredicate() returns Predicate
//parseExpression() returns Parameter
//You would need to modify the match function to return the Token's string value
//Different solution : make temporary variables as data members of Parser
//This way you could only add code instead of modifying code you've already written 

#endif //PARSER_H