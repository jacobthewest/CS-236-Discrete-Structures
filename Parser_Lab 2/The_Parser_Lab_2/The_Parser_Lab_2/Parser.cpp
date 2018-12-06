#include "Parser.h"

Parser::Parser(vector<Token*> tokenList) {
	index_m = 0;
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
		else if (currentToken->getTokenType() == EOF_TYPE) {
			throw string(currentToken->toString());
		}
	}

}
void Parser::parseScheme() {
	//scheme   	-> 	headPredicate
	/* SOME CONTROVERSY HERE AMONG THE GITHUBS. Woodfield and Barker have a different
	   grammar for sheme ->. The one above this multiline comment is from Barker. I 
	   will use Barker's. I am guessing that adding the scheme to the datalogProgramObject
	   will be after I parse the head predicate
	*/
	predicateObject = Predicate(currentToken->getValue());
	parseHeadPredicate();
	datalogProgramObject.addScheme(predicateObject); //Is this correct? Who knows... Yup, pretty sure that it is
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
		parseExpression();
	}
}
void Parser::parseExpression() {
	//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	ostringstream expressionOss;

	match(LEFT_PAREN);
	expressionOss << "(";
	parseId(expressionOss);
	parseOperator(expressionOss);
	parseId(expressionOss);	
	expressionOss << ")";

	predicateObject.addParameter(Parameter("EXPRESSION", expressionOss.str()));

	match(RIGHT_PAREN);

}
void Parser::parseOperator(ostringstream &expressionOss) {
	//operator	->	ADD | MULTIPLY
	if (currentToken->getTokenType() == ADD) {
		match(ADD);
		expressionOss << "+";
	}
	if (currentToken->getTokenType() == MULTIPLY) {
		match(MULTIPLY);
		expressionOss << "*";
	}
}

void Parser::parseId(ostringstream &expressionOss) {
	if (currentToken->getTokenType() == ID) {
		expressionOss << currentToken->getValue();
		match(ID);
	}
}