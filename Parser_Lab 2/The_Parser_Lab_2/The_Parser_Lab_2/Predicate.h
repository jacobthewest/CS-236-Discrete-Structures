#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"

#include <iostream>

using namespace std;

//Predicate is the parent of Schemes, Facts, and Queries
class Predicate { //ID LEFT_PAREN parameter prameterList RIGHT_PAREN
private:
	string id;
protected:
	std::vector<Parameter> parametersVector;
public:

	//----Constructors----//
	Predicate() {};
	Predicate(string identifier);
	Predicate(string identifier, vector<Parameter> parameterList);
	~Predicate() {};

	vector<Parameter> getVectorOfParameters() { return this->parametersVector; }
	string getId() { return this->id; }
	string toString();
	void addParameter(Parameter parameterToAdd);
};

#endif //PREDICATE_H