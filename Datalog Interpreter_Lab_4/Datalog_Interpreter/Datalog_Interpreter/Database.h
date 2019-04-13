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
	vector<Rule> rules_m;
	vector<Predicate> queries_m;
	vector<Relation> relations_m;

	vector<size_t> parameterPositions_m;
	vector<string> parametersThatAreIDs_m;

	size_t numTimesCycledThroughRules_m;
public:

	//Constructors
	Database() {};
	Database(vector<Predicate> schemes, vector<Predicate> facts, vector<Rule> rules, vector<Predicate> queries);
	~Database() {};

	void addRelation(Relation& relationObj);
	void addRowToRelation(Tuple& tupleObj);
	void evaluateQueries();
<<<<<<< HEAD
	void printTheStuffBeforePrintingTuples(Relation tempRelation, vector<string> paramatersThatAreIDs,
		vector<Parameter> parametersFromTempRelation, bool lastQuery);
	void checkForDuplicateParameters(vector<string>& parametersThatAreIDs_m, bool& duplicateParameterExists,
=======
	void printTheStuffBeforePrintingTuples(Relation& tempRelation, vector<string>& paramatersThatAreIDs, 
		vector<Parameter>& parametersFromTempRelation, bool& lastQuery);
	void checkForDuplicateParameters(vector<string>& parametersThatAreIDs_m, bool& duplicateParameterExists, 
>>>>>>> 226d670368832cf963a572f4796ef875c5396d3a
		size_t& positionOfDuplicateParameter, string& parameterValue);

	//Lab 4 Functions
	void evaluateRules();
	void evaluateSingleRule(Rule& ruleToBeEvaluated, int& currRuleIndex);
	Relation evaluatePredicate(Predicate& predicate);
	vector<Parameter> getRuleHeadPredAsVectorOfParams(Rule& ruleToBeEvaluated);
	size_t findTotalTuples();
	void union_function(Relation& newRelation, int& currRuleIndex);
	void printLab4();

};

#endif //DATABASE_H