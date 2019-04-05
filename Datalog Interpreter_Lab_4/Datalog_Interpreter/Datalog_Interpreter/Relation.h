#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include "Scheme.h"

#include <iostream>
#include <set>


using namespace std;

class Relation {

private:

	string name_m;
	Scheme header_m;  //List of attribute names (this is a vector<Parameter>)
	set<Tuple> tuples_m; //The collection of tuples for each relation //A list of attribute values

public:

	//Constructors			
	Relation() {};
	Relation(string name, Scheme header); //Can be initialized with an empty set of tuples
	~Relation() {};

	//Other functions
	void addTuple(Tuple tupleToAdd);
	string toString();
	Relation select(size_t positionInParametersVector, string parameterValue);
	Relation select(size_t positionInColumnOne, size_t positionInColumnTwo);
	Relation project(vector<size_t> parameterPositions);
	Relation rename(vector<string> parametersThatAreIDs);

	void printTuples(vector<string> parametersThaAreIDs, size_t numTuples, bool lastQuery);
	void printTuplesForTempTuple(vector<string>& parametersThaAreIDs, Tuple& tempTuple, size_t& j,
		bool& lastQuery, size_t& numTuplesOutputted);
	void printSingleTupleWithSpace(bool lastQuery, Tuple tempTuple, size_t tempColumn, size_t j, vector<string> parametersThaAreIDs);
	void printSingleTupleWithNoSpace(bool lastQuery, Tuple tempTuple, size_t tempColumn, size_t j, 
		vector<string> parametersThaAreIDs, size_t& numTuplesOutputted);

	//Getters and setters
	void setRelationName(string relationName) { this->name_m = relationName; }
	string getRelationName() { return this->name_m; }
	void setHeader(Scheme header) { this->header_m = header; }
	Scheme getHeader() { return this->header_m; }
	size_t getNumTuples() { return this->tuples_m.size(); }
	size_t getNumTuplesInRelationForOutput(vector<string> parametersThatAreIDs);
	Relation projectLab4(vector<size_t> parameterPositions);
	Relation renameLab4(vector<string> parametersThatAreIDs);
	void setTuples(set<Tuple> tuples) { this->tuples_m = tuples; }

	//Project 4 Functions
	Relation join_function(vector<Relation> relationsFromPredicates);
	Scheme combineSchemes(vector<Relation> relationsFromPredicates);
	bool isJoinable(Tuple t1, Tuple t2, Scheme s1, Scheme s2);
	Tuple combineTuples(Tuple t1, Tuple t2, Scheme s1, Scheme s2, Scheme newSchemeForRelation);
	set<Tuple> getTuples() { return tuples_m; }
	Relation projectNewRelation(Relation newRelation, vector<size_t> parameterPositionsWeCareAboutFromNewScheme, 
		vector<Parameter> columnsWeNeeds, string stringOfNewScheme);
	void printTuplesLab4(vector<string> parametersThaAreIDs, size_t numTuples);
	void printTuplesForTempTupleLab4(vector<string>& parametersThaAreIDs, Tuple& tempTuple, size_t& j,
		size_t& numTuplesOutputted);
	void printSingleTupleWithSpaceLab4(Tuple tempTuple, size_t tempColumn, size_t j,
		vector<string> parametersThaAreIDs);
	void printSingleTupleWithNoSpaceLab4(Tuple tempTuple, size_t tempColumn, size_t j,
		vector<string> parametersThaAreIDs, size_t& numTuplesOutputted);
};

#endif //RELATION_H