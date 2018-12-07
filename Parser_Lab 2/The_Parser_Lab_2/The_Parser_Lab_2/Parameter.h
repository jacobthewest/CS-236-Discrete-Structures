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
	Parameter(string type_m, string value_m);
	~Parameter() {};
	string toString();
	string getType() { return type_m; }
	string getValue() { return value_m; }
};
#endif //PARAMETER_H