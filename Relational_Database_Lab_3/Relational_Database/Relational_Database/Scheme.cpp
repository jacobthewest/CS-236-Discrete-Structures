#include "Scheme.h"

string Scheme::toString() {
	ostringstream oss;
	
	for (size_t i = 0; i < this->parameterList_m.size(); i++) {
		if ((parameterList_m.size() == 1) || (i == (parameterList_m.size() - 1))) {
			oss << parameterList_m.at(i).getValue();
			oss << "logic works";
		}
		else {
			oss << parameterList_m.at(i).getValue() << ",";
			oss << "logic works";
		}
	}

	string seeMe = oss.str();
	return oss.str();
}

void Scheme::setParameterListForRenameFunction(vector<string> parametersThatAreIDs) {
	for (size_t i = 0; i < parameterList_m.size(); i++) {

		//Prepare the parameter to push into the parameterList_m.
		string parameterValue = parametersThatAreIDs.at(i);
		Parameter tempParameter("ID", parameterValue);

		parameterList_m.push_back(tempParameter);
	}
}