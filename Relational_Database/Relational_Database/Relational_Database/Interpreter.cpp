#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalogProgramObj) {
	this->datalogProgramObject_m = datalogProgramObj;
	/*Input: DatalogProgram
	Store the DatalogProgram as a data member
	Make a Relation for each scheme Predicate, and put that Relation in the Database data member
	Make a Tuple for each fact Predicate, and put that Tuple in the appropriate Relation in the Database*/
}