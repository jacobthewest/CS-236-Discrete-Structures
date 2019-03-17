#ifndef SCHEME_H
#define SCHEME_H

#include "Parameter.h"

#include <iostream>

using namespace std;

class Scheme {

private:
	vector<Parameter> parameterList_m;
public:

	//Constructors
	Scheme() {};
	~Scheme() {};

	//Other functions
	void addParameterList(vector<Parameter> parameterList) { this->parameterList_m = parameterList; }
	vector<Parameter> getParameterList() { return this->parameterList_m; }
	string toString();
	void setParameterListForRenameFunction(vector<string> parametersThatAreIDs);

};

#endif //SCHEME_H