#include "Rule.h"

Rule::Rule(Predicate predicate) {
	this->predicate_m = predicate;
}

Rule::Rule(Predicate predicate, vector<Predicate> predicateList) {
	this->predicate_m = predicate;
	this->predicateList_m = predicateList_m;
}

void Rule::addPredicate(Predicate predicate) {
	this->predicateList_m.push_back(predicate);
}

string Rule::toString() {
	ostringstream oss;

	oss << predicate_m.toString() << " :- ";

	for (size_t i = 0; i < predicateList_m.size(); i++) {
		switch (i) {
		case 0:
			oss << predicateList_m.at(i).toString();
			break;
		default:
			oss << "," << predicateList_m.at(i).toString();
			break;
		}
	}
	oss << ".";
	return oss.str();
}

vector<size_t> Rule::getPositionOfParamsWeCareAbout(vector<Parameter> combinedScheme, vector<Parameter> schemeOfProject) {
	vector<size_t> returnMe;
	for (size_t i = 0; i < schemeOfProject.size(); i++) {
		for (size_t j = 0; j < combinedScheme.size(); j++) {
			if (schemeOfProject.at(i).getValue() == combinedScheme.at(j).getValue()) {
				returnMe.push_back(j);
			}
		}
	}

	return returnMe;
}