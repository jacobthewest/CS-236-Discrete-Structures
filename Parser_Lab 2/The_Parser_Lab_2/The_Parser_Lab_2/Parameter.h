#ifndef PARAMETER_H
#define PARAMETER_H

#include "Lexer.h"
#include <iostream>

using namespace std;

class Parameter { //string | ID | expression
private:
	string type_m;
	string value_m;
public:
	
	Parameter() {};
	Parameter(string type_m, string value_m) {};
	~Parameter() {};
	string toString();
};


//----------Note For Constructors: We have access to the Token Types becausue Lexer.h contains Token.h -----------------//
	//Parameter() {};
	//static void createParameter(Lexer lexerObj) {
	//	switch (/*CurentTokenType*/) {
	//	case STRING: 
	//		//new string;
	//		//Add to parameter vector
	//		break;
	//	case ID:
	//		//new ID
	//		break;
	//	default:
	//		//new expression
	//		//The grammar suggests that an expression has a left parameter, an operator, 
	//		//and a right parameter.You should create expression objects that contain these 
	//		//three things.Since a parameter object can hold an expression, this allows for arbitrarily nested expressions.
	//		break;
	//	}
	//}

//Parameter is an abstract class
//static Parameter createParameter(Lex lex)
//	calls : new Id(lex)
//	calls : new String(lex)
//	calls : new Expression(lex)

#endif //PARAMETER_H