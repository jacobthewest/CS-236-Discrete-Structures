#include "Relation.h"

Relation::Relation(string name, Scheme header) {
	this->name_m = name;
	this->header_m = header;
}

void Relation::addTuple(Tuple tupleToAdd) {
	this->tuples_m.insert(tupleToAdd);
}

string Relation::toString() {
	ostringstream oss;

	//Print the first line
	oss << " (" << this->header_m.toString() << ")?";

	oss << " Yes(" << tuples_m.size() << ")" << endl;


	//Now print the tuples (aka rows) in the database	

	for (set<Tuple>::iterator i = tuples_m.begin(); i != tuples_m.end(); i++) {
		//How to iterate through a set-- https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
		Tuple tempTuple = *i;
		oss << tempTuple.toString();
	}

	cout << oss.str();
	return oss.str();
}

Relation Relation::select(size_t positionInParametersVector, string parameterValue) {
	/*Create a reltion and give it the name and header of the current relation we are working in*/
	Relation tempRelation;
	tempRelation.name_m = this->name_m;
	tempRelation.header_m = this->header_m;

	/*Iterate through the set of tuples that this current relation has*/
	set<Tuple>::iterator tupleIterator = tuples_m.begin();

	for (size_t i = 0; i < tuples_m.size(); i++) {
		Tuple tempTuple = *tupleIterator;
		
		//Get the value of our tuple at the specific position we are searching for
		string tempTupleValueAtPositionInParametersVector;
		tempTupleValueAtPositionInParametersVector = tempTuple.getElementFromTupleList(positionInParametersVector);

		/*If our parameterValue has the same value at the positionInParametersVector as any tuple does in our tuple set, then
		we will add it to our tempRelation*/
		if (tempTupleValueAtPositionInParametersVector == parameterValue) {
			tempRelation.addTuple(tempTuple);
		}

		tupleIterator++;
	}

	return tempRelation;
}

Relation Relation::select(size_t positionInColumnOne, size_t positionInColumnTwo) {
	/*Create a reltion and give it the name and header of the current relation we are working in*/
	Relation tempRelation;
	tempRelation.name_m = this->name_m;
	tempRelation.header_m = this->header_m;

	/*Iterate through the set of tuples that this current relation has*/
	set<Tuple>::iterator tupleIterator = tuples_m.begin();

	for (size_t i = 0; i < tuples_m.size(); i++) {
		Tuple tempTuple = *tupleIterator;

		//Get the value of our tuple at the specific position we are searching for
		string columnOneValue;
		columnOneValue = tempTuple.getElementFromTupleList(positionInColumnOne);

		string columnTwoValue;
		columnTwoValue = tempTuple.getElementFromTupleList(positionInColumnTwo);

		/*If our parameterValue has the same value at the positionInParametersVector as any tuple does in our tuple set, then
		we will add it to our tempRelation*/
		if (columnOneValue == columnTwoValue) {
			tempRelation.addTuple(tempTuple);
		}

		tupleIterator++;
	}

	return tempRelation;
}

Relation Relation::project(vector<size_t> parameterPositions) {
	/*Create a reltion and give it the name and header of the current relation we are working in*/
	Relation relationToReturn;
	relationToReturn.name_m = this->name_m;
	relationToReturn.header_m = this->header_m;

	//Make a tuple set iterator;
	set<Tuple>::iterator tuples_mIterator = tuples_m.begin();

	//A tuple to project (add) to our tempRelationToReturn at the end of this function
	Tuple tupleToProject;

	//Iterate through every tuple that we have for the relation that we are currently working in
	for (size_t i = 0; i < tuples_m.size(); i++) {
		
		//Create a tempTuple
		Tuple tempTuple = *tuples_mIterator;
		
		//Iterate through all of the tuple values that the tempTuple has and add them to the tupleToProject
		for (size_t j = 0; j < parameterPositions.size(); j++) {
			string tupleValueToAdd = tempTuple.getElementFromTupleList(j);
			tupleToProject.addToTupleList(tupleValueToAdd);
		}
	}
	
	//Add tupleToProject (the tuple we have been straightup loading with tuple values) to the relation
	relationToReturn.addTuple(tupleToProject);

	//In case tuples_m is empty then we will send back an empty relation
	if (tuples_m.size() == 0) {
		Relation emptyReltion;
		return emptyReltion;
	}
	else { return relationToReturn; }
}

Relation Relation::rename(vector<string> parametersThatAreIDs) {
	/*The rename operation changes the scheme of the relation. The resulting relation has the 
	same tuples (and name) as the original*/
	Relation relationToReturn;
	relationToReturn.name_m = this->name_m;
	relationToReturn.tuples_m = this->tuples_m;

	/*This will set the parameterlist for relationToReturn. In our solution so far, we have only interacted with the Scheme
	class in our Database class constructor when we added the parameters to the data member schemes_m through the addParameterList
	function. Right now, relationToReturn doesn't have a populated vector<Parameter> parameterList_m set for it's header_m datamember.
	What we do below will fill that up for us.*/
	relationToReturn.header_m.setParameterListForRenameFunction(parametersThatAreIDs);

	return relationToReturn;
}