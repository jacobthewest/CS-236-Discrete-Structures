#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"

#include <iostream>

class Interpreter {

private:
	DatalogProgram datalogProgramObject_m;
public:
	//Constructors
	Interpreter() {};
	Interpreter(DatalogProgram datalogProgramObj);

	~Interpreter() {};

};

#endif	//INTERPRETER_H