#include "DatalogProgram.h"

string DatalogProgram::toString() {
	ostringstream oss;
	oss << schemesToString();
	oss << factsToString();
	oss << rulesToString();
	oss << queriesToString();
	oss << domainToString();
	return oss.str();
}

string DatalogProgram::schemesToString() {
	ostringstream oss;
	oss << "Schemes(" << schemes_m.size() << "):" << endl;
	for (size_t i = 0; i < schemes_m.size(); i++) {
		oss << "  " << schemes_m.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::factsToString() {
	ostringstream oss;
	oss << "Facts(" << facts_m.size() << "):" << endl;
	for (size_t i = 0; i < facts_m.size(); i++) {
		oss << "  " << facts_m.at(i).toString() << "." << endl;
	}
	return oss.str();
}
string DatalogProgram::rulesToString() {
	ostringstream oss;
	oss << "Rules(" << rules_m.size() << "):" << endl;
	for (size_t i = 0; i < rules_m.size(); i++) {
		oss << "  " << rules_m.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::queriesToString() {
	ostringstream oss;
	oss << "Queries(" << queries_m.size() << "):" << endl;
	for (size_t i = 0; i < queries_m.size(); i++) {
		oss << "  " << queries_m.at(i).toString() << "?" << endl;
	}
	return oss.str();
}
string DatalogProgram::domainToString() {
	ostringstream oss;
	oss << "Domain(" << domain_m.size() << "):";
	if (domain_m.size() > 0) { oss << endl; }

	//How to iterate through a set-- https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
	set<string>::iterator setIterator;
	setIterator = domain_m.begin();
	for (size_t i = 0; i < domain_m.size(); i++) {
		if (i == domain_m.size() - 1) { oss << "  " << (*setIterator); }
		else { oss << "  " << (*setIterator) << endl; }
		setIterator++;
	}

	return oss.str();
}

void DatalogProgram::addScheme(Predicate schemeToAdd) {
	schemes_m.push_back(schemeToAdd);
}
void DatalogProgram::addFact(Predicate factToAdd) {
	addDomain(factToAdd.getVectorOfParameters());
	facts_m.push_back(factToAdd);
}
void DatalogProgram::addRule(Rule ruleToAdd) {
	addDomain(ruleToAdd.getPredicate().getVectorOfParameters());
	rules_m.push_back(ruleToAdd);
}
void DatalogProgram::addQuery(Predicate queryToAdd) {
	queries_m.push_back(queryToAdd);
}
void DatalogProgram::addDomain(vector<Parameter> parameterList) {
	for (size_t i = 0; i < parameterList.size(); i++) {
		if (parameterList.at(i).getType() == "STRING") {
			//insert function handles alphabetical sorting and prevents duplicates in set
			this->domain_m.insert(parameterList.at(i).getValue()); 
		}
	}	
}