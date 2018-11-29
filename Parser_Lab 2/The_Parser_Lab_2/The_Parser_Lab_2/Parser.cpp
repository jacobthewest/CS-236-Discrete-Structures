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
	parseHeadPredicate();
}
void Parser::parseFact() {
	//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	match(ID);
	match(LEFT_PAREN);
	match(STRING);
	parseStringList();
	match(RIGHT_PAREN);
	match(PERIOD);
}
void Parser::parseRule() {
	//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
	parseHeadPredicate();
	match(COLON_DASH);
	parsePredicate();
	parsePredicateList();
	match(PERIOD);
}
void Parser::parseQuery() {
	//query	        ->      predicate Q_MARK
	parsePredicate();
	match(Q_MARK);
}
void Parser::parseHeadPredicate() {
	//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
	match(ID);
	match(LEFT_PAREN);
	match(ID);
	parseIdList();
	match(RIGHT_PAREN);
}
void Parser::parsePredicate() {
	//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	match(ID);
	match(LEFT_PAREN);
	parseParameter();
	parseParameterList();
	match(RIGHT_PAREN);
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
	match(STRING);
	if (currentToken->getTokenType() == COMMA) {
		parseStringList();
	}
}
void Parser::parseIdList() {
	//idList  	-> 	COMMA ID idList | lambda
	match(COMMA);
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
		match(currentToken->getTokenType());
	}
	else {
		parseExpression();
	}
}
void Parser::parseExpression() {
	//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	match(LEFT_PAREN);
	parseParameter();
	parseOperator();
	parseParameter();
	match(RIGHT_PAREN);
}
void Parser::parseOperator() {
	//operator	->	ADD | MULTIPLY
	if (currentToken->getTokenType() == ADD) {
		match(ADD);
	}
	if (currentToken->getTokenType() == MULTIPLY) {
		match(MULTIPLY);
	}
}