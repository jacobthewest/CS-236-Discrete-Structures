#ifndef DATABASE_H
#define DATABASE_H

#include "Interpreter.h"
#include "Relation.h"

#include <iostream>
#include <map>

using namespace std;


class Database {

private:
	map<string, Relation> relationMap_m; //Key:string Value: Relation

	vector<Predicate> schemes_m;
	vector<Predicate> facts_m;
	vector<Predicate> queries_m;
	vector<Relation> relations_m;

	vector<size_t> parameterPositions_m;
	vector<string> parametersThatAreIDs_m;
public:

	//Constructors
	Database() {};
	Database(vector<Predicate> schemes, vector<Predicate> facts, vector<Predicate> queries);
	~Database() {};

	void addRelation(Relation relationObj);
	void addRowToRelation(Tuple tupleObj);
	void evaluateQueries();
	void printTheStuffBeforePrintingTuples(Relation tempRelation, vector<string> paramatersThatAreIDs, 
		vector<Parameter> parametersFromTempRelation, bool lastQuery);
	void checkForDuplicateParameters(vector<string>& parametersThatAreIDs_m, bool& duplicateParameterExists, 
		size_t& positionOfDuplicateParameter, string& parameterValue);
};

#endif //DATABASE_H