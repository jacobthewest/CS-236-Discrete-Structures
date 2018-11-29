#include "Rule.h"

Rule::Rule(Predicate predicate, vector<Predicate> predicateList) {
	this->predicate_m = predicate;
	this->predicateList_m = predicateList_m;
}

void Rule::addPredicate(Predicate predicate) {
	this->predicateList_m.push_back(predicate);
}

string Rule::toString() {
	ostringstream oss;

	oss << " :- " << predicate_m.toString();

	for (size_t i = 0; i < predicateList_m.size(); i++) {
		switch (i) {
		case 0:
			oss << predicateList_m[i].toString();
			break;
		default:
			oss << "," << predicateList_m[i].toString();
			break;
		}
	}
	return oss.str();
}