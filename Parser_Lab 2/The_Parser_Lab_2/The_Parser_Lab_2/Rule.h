#ifndef RULE_H
#define RULE_H

#include "Predicate.h"

#include <iostream>
#include <vector>

using namespace std;

class Rule { //headPredicate COLON_DASH predicate predicateList PERIOD

private:
	Predicate predicate_m;
	vector<Predicate> predicateList_m;
public:
	Rule() {};
	Rule(Predicate predicate);
	Rule(Predicate predicate, vector<Predicate> predicateList);
	~Rule() {};

	string toString();
	vector<Predicate> getPredicateList() { return this->predicateList_m; }
	Predicate getPredicate() { return this->predicate_m; }
	void addPredicate(Predicate predicate);
};

#endif RULE_H

