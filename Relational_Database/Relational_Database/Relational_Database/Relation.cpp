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
	relationToReturn.setRelationName(this->name_m);
	relationToReturn.setHeader(this->header_m);

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
			size_t getValueFromTupleListAtThisParameterPosition = parameterPositions.at(j);
			string tupleValueToAdd = tempTuple.getElementFromTupleList(getValueFromTupleListAtThisParameterPosition);
			tupleToProject.addToTupleList(tupleValueToAdd);
		}
		
		tuples_mIterator++;
	}
	
	//Add tupleToProject (the tuple we have been straightup loading with tuple values) to the relation
	relationToReturn.addTuple(tupleToProject);

	//In case tuples_m is empty then we will send back an empty relation
	if (tuples_m.size() == 0) {
		Relation emptyRelation;
		emptyRelation.setRelationName(this->getRelationName());
		emptyRelation.setHeader(this->getHeader());
		return emptyRelation;
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

size_t Relation::getNumTuplesInRelationForOutput(vector<string> parametersThatAreIDs) {
	
	size_t numTuples = 0;

	//Count the number of tuples
	set<Tuple>::iterator i;
	for (i = tuples_m.begin(); i != tuples_m.end(); i++) {
		Tuple tempTuple = *i;

		for (size_t j = 0; j < tempTuple.getTupleListSize(); j++) {
			numTuples++;
		}
	}

	/*Because we print only the tuples that are associated with an ID, we want to return the number of tuple pairs that
	have an ID.*/

	if (numTuples != 0) {
		return (numTuples / parametersThatAreIDs.size());
	}
	
	/* We have no IDs associated with what we need to print, so that means that we have a query that is searching for a specific
	value pair. Because of the integer division, we can lose values so we will return 1. i.e. (tuples_m.size() / zero ID's) will
	give us a zero, but we were put into this function because we said that tuples_m.size() > 0, so we know that there is something
	in there. Also, for a value value pair, we don't have ID's associated with the number of tuples, so we will just return 1, because
	a set will hold only one copy of each value value pair.*/
	else { return 1; }
}

void Relation::printTuples(vector<string> parametersThatAreIDs, size_t numTuples, bool lastQuery) {


	set<Tuple>::iterator tupleIterator = tuples_m.begin();

	for (size_t i = 0; i < tuples_m.size(); i++) {

		Tuple tempTuple = *tupleIterator;
		size_t numTuplesOutputted = 0;
		
		for (size_t j = 0; j < tempTuple.getTupleListSize(); j++) {
			printTuplesForTempTuple(parametersThatAreIDs, tempTuple, j, lastQuery, numTuplesOutputted);
		}
		tupleIterator++;
	}
}

void Relation::printTuplesForTempTuple(vector<string>& parametersThatAreIDs, Tuple& tempTuple, size_t& j,
	bool& lastQuery, size_t& numTuplesOutputted) {
	size_t tempColumn = j % parametersThatAreIDs.size();
	/*
		this little algorithm above will always keep the column within the correct bounds.
		example: table (aka relation) with 3 parameters
			"tempcolumn" will always be set in this pattern: 0, 1, 2; this is good because it matches with our "3 column" vector
		example: table (aka reltion) with 2 parameters
			"tempcolumn" will always be set in this pattern: 0, 1; this is good because it matches with our "3 column" vector
		to see how it works better, run with barker's in62.txt test case and set a breakpoint on "column"
	*/

	if (parametersThatAreIDs.size() < 2) {
		/*
			if parametersthatareids.size() < 2
			this has to do with the query. the query may have parameters in it.

			example query with zero parameters:  sk('b','c')? parametersthatareids.size() would be zero
			example query with one parameter:  sk(a,'c')? parametersthatareids.size() would be one
			example query with two parameters:  sk(a,b)? parametersthatareids.size() would be two
		*/

		// We have a single id to print with its matching tuple value
		printSingleTupleWithSpace(lastQuery, tempTuple, tempColumn, j, parametersThatAreIDs);
	}
	else {

		/* lastColumnAsIndex is set to parametersthatareids.size() - 1 because we need to work with vectors which
		  are zero based*/
		size_t lastColumnAsIndex = parametersThatAreIDs.size() - 1;

		if (numTuplesOutputted == lastColumnAsIndex) {
			//if we are at the last item in our row and at the final column
			printSingleTupleWithNoSpace(lastQuery, tempTuple, tempColumn, j, parametersThatAreIDs, numTuplesOutputted);
		}
		else if (numTuplesOutputted == 0) {
			//if we are at the first item in the row in the first column
			cout << "  " << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << ", ";
			numTuplesOutputted++;
		}
		else {
			/* we are not at the first item in the row in the first column, we are somewhere in the
			   middle of the first and last columns*/
			cout << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << ", ";
			numTuplesOutputted++;
		}
	}
}

void Relation::printSingleTupleWithSpace(bool lastQuery, Tuple tempTuple, size_t tempColumn, 
	size_t j, vector<string> parametersThatAreIDs) {
	if (lastQuery && (j == tempTuple.getTupleListSize() - 1)) {
		cout << "  " << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j);
	}
	else {
		cout << "  " << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << endl;
	}
}

void Relation::printSingleTupleWithNoSpace(bool lastQuery, Tuple tempTuple, size_t tempColumn, 
	size_t j, vector<string> parametersThatAreIDs, size_t& numTuplesOutputted) {
	if (lastQuery && (j == tempTuple.getTupleListSize() - 1)) {
		cout << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j);
	}
	else {
		cout << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << endl;
	}
	numTuplesOutputted = 0; // Set numOutputted to zero so we can start printing for a new row				
}