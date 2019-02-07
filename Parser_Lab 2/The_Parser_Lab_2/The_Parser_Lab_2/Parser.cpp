#include "Parser.h"

Parser::Parser(vector<Token*> tokenList) {
	index_m = 0;
	this->trackingNum_m = 2; //Set to 2 because we will always have at least 2 parameters in an expression
	tokenListCopyForParserClass_m = tokenList;
	currentToken = tokenListCopyForParserClass_m.at(index_m);
	parseDatalogProgram();
}

void Parser::parseDatalogProgram() {
	/*
		datalogProgram	->	SCHEMES COLON scheme schemeList
			FACTS COLON factList
			RULES COLON ruleList
			QUERIES COLON query queryList
	*/
	match(SCHEMES);
	match(COLON);
	parseScheme();
	parseSchemeList();
	match(FACTS);
	match(COLON);
	parseFactList();
	match(RULES);
	match(COLON);
	parseRuleList();
	match(QUERIES);
	match(COLON);
	parseQuery();
	parseQueryList();
}

bool Parser::match(TokenType tokenType) {
	if (tokenType == currentToken->getTokenType()) {
		index_m++;
		currentToken = tokenListCopyForParserClass_m.at(index_m);
		return true;
	}
	else {
		throw string(currentToken->toString());
		return false;
	}
}

void Parser::parseSchemeList() {
	//schemeList	->	scheme schemeList | lambda

	if (currentToken->getTokenType() == ID) {
		parseScheme();
		if (currentToken->getTokenType() == ID) {
			parseSchemeList();
		}
	}
}

void Parser::parseFactList() {
	//factList	->	fact factList | lambda

	if (currentToken->getTokenType() == ID) {
		parseFact();
		if (currentToken->getTokenType() == ID) {
			parseFactList();
		}
	}

}

void Parser::parseRuleList() {
	//ruleList	->	rule ruleList | lambda
	if (currentToken->getTokenType() == ID) {
		parseRule();
		if (currentToken->getTokenType() == ID) {
			parseRuleList();
		}
	}
}

void Parser::parseQueryList() {
	//queryList	->	query queryList | lambda
	if (currentToken->getTokenType() == EOF_TYPE) {
	}
	else {
		parseQuery();
		if (currentToken->getTokenType() == ID) {
			parseQueryList();
		}
		/*else if (currentToken->getTokenType() == EOF_TYPE) {
			throw string(currentToken->toString());
		}*/
	}

}

void Parser::parseScheme() {
	//scheme   	-> 	headPredicate
	/* SOME CONTROVERSY HERE AMONG THE GITHUBS. Woodfield and Barker have a different
	   grammar for sheme ->. The one above this multiline comment is from Barker. I 
	   will use Barker's.
	*/
	predicateObject = Predicate(currentToken->getValue());
	parseHeadPredicate();
	datalogProgramObject.addScheme(predicateObject); 
}
void Parser::parseFact() {
	//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	predicateObject = Predicate(currentToken->getValue());
	match(ID);
	match(LEFT_PAREN);
	if (currentToken->getTokenType() == STRING) {
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
	}
	match(STRING);
	if (currentToken->getTokenType() == COMMA) {
		parseStringList();
	}
	match(RIGHT_PAREN);
	match(PERIOD);
	datalogProgramObject.addFact(predicateObject);
}
void Parser::parseRule() {
	//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD	
	parseHeadPredicate();
	ruleObject = Rule(predicateObject);
	match(COLON_DASH);
	parsePredicate();
	if (currentToken->getTokenType() == COMMA) {
		parsePredicateList();
	}	
	match(PERIOD);
	datalogProgramObject.addRule(ruleObject);
}
void Parser::parseQuery() {
	//query	        ->      predicate Q_MARK
	predicateObject = Predicate(currentToken->getValue());
	parsePredicate();
	match(Q_MARK); 
	datalogProgramObject.addQuery(predicateObject);
}
void Parser::parseHeadPredicate() {
	//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
	predicateObject = Predicate(currentToken->getValue());
	match(ID);
	match(LEFT_PAREN);
	if (currentToken->getTokenType() == ID) { 
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
	}
	match(ID);
	if (currentToken->getTokenType() == COMMA) {
		parseIdList();
	}
	match(RIGHT_PAREN);
}
void Parser::parsePredicate() {
	//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	predicateObject = Predicate(currentToken->getValue());
	match(ID);
	match(LEFT_PAREN);
	parseParameter();
	if (currentToken->getTokenType() == COMMA) {
		parseParameterList();
	}
	match(RIGHT_PAREN);
	ruleObject.addPredicate(predicateObject);
}
void Parser::parsePredicateList() {
	//predicateList->COMMA predicate predicateList | lambda
	match(COMMA);
	parsePredicate();
	if (currentToken->getTokenType() == COMMA) {
		parsePredicateList();
	}
}
void Parser::parseParameterList() {
	//parameterList	-> 	COMMA parameter parameterList | lambda
	match(COMMA);
	parseParameter();
	if (currentToken->getTokenType() == COMMA) {
		parseParameterList();
	}
}

void Parser::parseStringList() {
	//stringList	-> 	COMMA STRING stringList | lambda
	match(COMMA);
	if (currentToken->getTokenType() == STRING) {
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
	}
	match(STRING);
	if (currentToken->getTokenType() == COMMA) {
		parseStringList();
	}
}

void Parser::parseIdList() {
	//idList  	-> 	COMMA ID idList | lambda
	match(COMMA);
	if (currentToken->getTokenType() == ID) {
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
	}
	match(ID);
	if (currentToken->getTokenType() == COMMA) {
		parseIdList();
	}
}

void Parser::parseParameter() {
	/*
		parameter	->	STRING
		parameter	->	ID
		parameter	->	expression
	*/
	if (currentToken->getTokenType() == STRING || currentToken->getTokenType() == ID) {
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
		match(currentToken->getTokenType());
	}
	else {
		//cout << "parsing expression from the parameter function" << endl; system("pause");
		parseExpression(this->expressionString_m, trackingNum_m);
		this->expressionString_m = ""; //clear the string after all of the recursion and adding it to the predicateObject
		this->trackingNum_m = 2;
	}
}

void Parser::parseParameter(bool& doNotPrintBecauseOfExpression, string& expressionString_m, size_t& trackingNum_m) {
	/*
		parameter	->	STRING
		parameter	->	ID
		parameter	->	expression
	*/
	if (currentToken->getTokenType() == STRING || currentToken->getTokenType() == ID) {
		TokenType tokenType;
		tokenType = currentToken->getTokenType();
		if (!doNotPrintBecauseOfExpression) {
			predicateObject.addParameter(Parameter(currentToken->tokenTypeToString(tokenType), currentToken->getValue()));
			doNotPrintBecauseOfExpression = false;
		}		
		match(currentToken->getTokenType());
	}
	else if (currentToken->getTokenType() == LEFT_PAREN) {
		//cout << "parsing expression from the parameter function" << endl; system("pause");
		parseExpression(expressionString_m, trackingNum_m);
	}
	else {
		throw string(currentToken->toString());
	}
}

void Parser::parseExpression(string& expressionString_m, size_t& trackingNum_m) {
	//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	bool doNotPrintBecauseOfExpression = false;

	match(LEFT_PAREN);
	this->trackingNum_m++; //Increment because of a left paren
	expressionString_m += "(";
	if (currentToken->getValue() != "(") { 
		expressionString_m += currentToken->getValue();
		doNotPrintBecauseOfExpression = true;
	}
	parseParameter(doNotPrintBecauseOfExpression, expressionString_m, trackingNum_m);
	parseOperator(expressionString_m);
	if (currentToken->getValue() != ")" && currentToken->getValue() != "(") {
		expressionString_m += currentToken->getValue();
		doNotPrintBecauseOfExpression = true;
	}
	parseParameter(doNotPrintBecauseOfExpression, expressionString_m, trackingNum_m);
	expressionString_m += ")";
	match(RIGHT_PAREN);
	this->trackingNum_m--;

	if (this->trackingNum_m == 2) { //2 represents the original L-paren and R-paren
		predicateObject.addParameter(Parameter("EXPRESSION", expressionString_m));
	}

}
void Parser::parseOperator(string& expressionString_m) {
	//operator	->	ADD | MULTIPLY
	if (currentToken->getTokenType() == ADD) {
		match(ADD);
		expressionString_m += "+";
	}
	else if (currentToken->getTokenType() == MULTIPLY) {
		match(MULTIPLY);
		expressionString_m += "*";
	}
	else {
		throw string(currentToken->toString());
	}
}

void Parser::parseId(ostringstream &expressionOss) {
	if (currentToken->getTokenType() == ID) {
		expressionOss << currentToken->getValue();
		match(ID);
	}
}
