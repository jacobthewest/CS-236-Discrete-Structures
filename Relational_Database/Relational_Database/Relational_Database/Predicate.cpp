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
		oss << "(" << parametersVector.at(0).getValue() << ")";
	}
	else {
		oss << "(";
		for (size_t i = 0; i < parametersVector.size(); i++) {
			switch (i) {
			case 0:
				oss << parametersVector.at(i).getValue();
				break;
			default:
				oss << "," << parametersVector.at(i).getValue();
				break;
			}
		}
		oss << ")";
	}
	return oss.str();
}

vector<Parameter> Predicate::getVectorOfParameters() { 
	/*cout << "Vector of parameters: " << endl;
	for (size_t i = 0; i < parametersVector.size(); i++) {
		cout << "\tType at " << i << " :" << parametersVector.at(i).getType() << endl;
		cout << "\tValue at " << i << " :" << parametersVector.at(i).getValue() << endl << endl;
	}*/
	return this->parametersVector; 
}