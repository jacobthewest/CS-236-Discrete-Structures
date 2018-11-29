#include "Predicate.h"

Predicate::Predicate(string identifier, vector<Parameter> parameterList) {
	this->id = identifier;
	this->parametersVector = parameterList;
}

void Predicate::addParameter(Parameter parameterToAdd) {
	this->parametersVector.push_back(parameterToAdd);
}

string Predicate::toString() {
	ostringstream oss;

	for (size_t i = 0; i < parametersVector.size(); i++) {
		switch (i) {
		case 0:
			oss << parametersVector[i].toString();
			break;
		default:
			oss << "," << parametersVector[i].toString();
			break;
		}
	}
	return oss.str();
}