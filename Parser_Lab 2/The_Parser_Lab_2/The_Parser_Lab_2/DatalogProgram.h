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
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set<string> domain;
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


	//TA SLides
	/*We need :
		A vector of Predicates for the schemes
		A vector of Predicates for the facts
		A vector of Predicates for the queries
		A vector of Rules for the rules
		These four vectors need to be returned from the Parser for Lab 3 to use
		So we need to create a container class called DatalogProgram that holds these four vectors*/


};

#endif //DATALOG_PROGRAM_H