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
	oss << "Schemes(" << schemes.size() << ") :" << endl;
	for (size_t i = 0; i < schemes.size(); i++) {
		oss << "  " << schemes.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::factsToString() {
	ostringstream oss;
	oss << "Facts(" << facts.size() << ") :" << endl;
	for (size_t i = 0; i < facts.size(); i++) {
		oss << "  " << facts.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::rulesToString() {
	ostringstream oss;
	oss << "Rules(" << rules.size() << ") :" << endl;
	for (size_t i = 0; i < rules.size(); i++) {
		oss << "  " << rules.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::queriesToString() {
	ostringstream oss;
	oss << "Queries(" << queries.size() << ") :" << endl;
	for (size_t i = 0; i < queries.size(); i++) {
		oss << "  " << queries.at(i).toString() << endl;
	}
	return oss.str();
}
string DatalogProgram::domainToString() {
	ostringstream oss;
	oss << "Domain(" << domain.size() << ") :" << endl;

	//How to iterate through a set-- https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
	set<string>::iterator setIterator;
	for (setIterator = domain.begin(); setIterator != domain.end(); setIterator++) {
		oss << (*setIterator) << endl;
	}

	return oss.str();
}