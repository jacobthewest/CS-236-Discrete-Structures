#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"

#include <iostream>

using namespace std;

/* What I'm learning

---Websites---
	A predicate is defined as: ID LEFT_PAREN parameter parameterList RIGHT_PAREN. 
		This means a predicate object needs to store an ID and a list of parameters.
	A class to represent a predicate needs to store the ID, and a list of parameters.
	Woodfield says to have more child classes for Scheme, Facts, and Queries. Barker says no need. So it's an opinion.
---TheParser PowerPoint--
	Because Id, Strng, and Expression inherit from Parameter, they can be created and stored in the variable parameters
---TA PowerPoint---
	Schemes, Facts, and Queries are just predicates
*/

//Are parents of Schemes, Facts, and Queries
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
	string toString(); //TA Slides said to do this
	void addParameter(Parameter parameterToAdd);
};

#endif //PREDICATE_H