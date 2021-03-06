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
};

#endif //RELATION_H