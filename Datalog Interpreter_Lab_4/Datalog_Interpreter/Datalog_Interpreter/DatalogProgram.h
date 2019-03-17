#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "Rule.h"
#include "Lexer.h"
#include "Predicate.h"

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class DatalogProgram {
private:
	vector<Predicate> schemes_m;
	vector<Predicate> facts_m;
	vector<Predicate> queries_m;
	vector<Rule> rules_m;
	set<string> domain_m;
public:
	//Contstructor
	DatalogProgram() {};
	~DatalogProgram() {};
	string toString();
	string schemesToString();
	string factsToString();
	string rulesToString();
	string queriesToString();
	string domainToString();

	void addScheme(Predicate schemeToAdd);
	void addFact(Predicate factToAdd);
	void addRule(Rule ruleToAdd);
	void addQuery(Predicate queryToAdd);
	void addDomain(vector<Parameter> parameterList);

	vector<Predicate> getSchemes() { return this->schemes_m; }
	vector<Predicate> getFacts() { return this->facts_m; }
	vector<Rule> getRules() { return this->rules_m; }
	vector<Predicate> getQueries() { return this->queries_m; }	
};

#endif //DATALOG_PROGRAM_H