#include "Predicate.h"

Predicate::Predicate(string identifier) {
	this->id = identifier;
}

Predicate::Predicate(string identifier, vector<Parameter> parameterList) {
	this->id = identifier;
	this->parametersVector = parameterList;
}

void Predicate::addParameter(Parameter parameterToAdd) {
	this->parametersVector.push_back(parameterToAdd);
}

string Predicate::toString() {
	ostringstream oss;

	oss << getId();

	if (parametersVector.size() == 1) {
		oss << "(" << parametersVector.at(0).toString() << ")";
	}
	else {
		oss << "(";
		for (size_t i = 0; i < parametersVector.size(); i++) {
			switch (i) {
			case 0:
				oss << parametersVector.at(i).toString();
				break;
			default:
				oss << "," << parametersVector.at(i).toString();
				break;
			}
		}
		oss << ")";
	}
	return oss.str();
}