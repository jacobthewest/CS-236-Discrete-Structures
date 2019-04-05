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

Relation Relation::join_function(vector<Relation> relationsFromPredicates) {

	//CombineSchemes
	Scheme newSchemeForRelation;
	newSchemeForRelation = combineSchemes(relationsFromPredicates);

	while (true) {

		if (relationsFromPredicates.size() == 1) {
			relationsFromPredicates.at(0).setHeader(newSchemeForRelation);
			return relationsFromPredicates.at(0);
		}
		else {
			Relation r1 = relationsFromPredicates.at(0);
		Relation r2 = relationsFromPredicates.at(1);
		Relation tempRel;

		set<Tuple> set1 = r1.getTuples();
		set<Tuple> set2 = r2.getTuples();

		Scheme s1 = r1.getHeader();
		Scheme s2 = r2.getHeader();

		for (Tuple t1 : set1) {
			for (Tuple t2 : set2) {
				//isJoinable
				if (isJoinable(t1, t2, s1, s2)) {
					//combineTuples
					// join t1 and t2 to make tuple t. add tuple t to relation r
					Tuple tempTuple = combineTuples(t1, t2, s1, s2, newSchemeForRelation);
					tempRel.addTuple(tempTuple);
				}
			}
		}

		/*Currently tempRel's tuples are up to date, but not its name and header. 
		  luckily, we only need to set its header*/
		vector<Relation> tempRelations;
		tempRelations.push_back(r1);
		tempRelations.push_back(r2);
		Scheme tempScheme = combineSchemes(tempRelations);
		tempRel.setHeader(tempScheme);

		//We have now worked through the relations. Time to fix the Relations in our vector
		relationsFromPredicates.at(1) = tempRel;

		//Pop the "old new" relation
		relationsFromPredicates.erase(relationsFromPredicates.begin());

		if (relationsFromPredicates.size() == 1) { 
			relationsFromPredicates.at(0).setHeader(newSchemeForRelation);
			return relationsFromPredicates.at(0); 
		}
		}		
	}
}

//void Relation::union_unction() {
	/*make the scheme s for the result relation
	(combine r1's scheme with r2's scheme)

		make a new empty relation r using scheme s

		for each tuple t1 in r1
			for each tuple t2 in r2

				if t1 and t2 can join
					join t1 and t2 to make tuple t
					add tuple t to relation r
					end if

					end for
					end for*/
//}

Relation Relation::projectLab4(vector<size_t> parameterPositions) {
	/*Create a reltion and give it the name and header of the current relation we are working in*/
	Relation relationToReturn;
	relationToReturn.setRelationName(this->name_m);
	relationToReturn.setHeader(this->header_m);

	//Make a tuple set iterator;
	set<Tuple>::iterator tuples_mIterator = tuples_m.begin();


	//Iterate through every tuple that we have for the relation that we are currently working in
	for (size_t i = 0; i < tuples_m.size(); i++) {
		//A tuple to project (add) to our tempRelationToReturn at the end of this function
		Tuple tupleToProject;

		//Create a tempTuple
		Tuple tempTuple = *tuples_mIterator;

		//Iterate through all of the tuple values that the tempTuple has and add them to the tupleToProject
		for (size_t j = 0; j < parameterPositions.size(); j++) {
			size_t getValueFromTupleListAtThisParameterPosition = parameterPositions.at(j);
			string tupleValueToAdd = tempTuple.getElementFromTupleList(getValueFromTupleListAtThisParameterPosition);
			tupleToProject.addToTupleList(tupleValueToAdd);
		}

		//Add tupleToProject (the tuple we have been straightup loading with tuple values) to the relation
		relationToReturn.addTuple(tupleToProject);


		tuples_mIterator++;
	}


	//In case tuples_m is empty then we will send back an empty relation
	if (tuples_m.size() == 0) {
		Relation emptyRelation;
		emptyRelation.setRelationName(this->getRelationName());
		emptyRelation.setHeader(this->getHeader());
		return emptyRelation;
	}
	else { return relationToReturn; }
}

Relation Relation::renameLab4(vector<string> parametersThatAreIDs) {
	/*The rename operation changes the scheme of the relation. The resulting relation has the
	same tuples (and name) as the original*/
	Relation relationToReturn;
	relationToReturn.name_m = this->name_m;
	relationToReturn.tuples_m = this->tuples_m;	

	/*This will set the parameterlist for relationToReturn. In our solution so far, we have only interacted with the Scheme
	class in our Database class constructor when we added the parameters to the data member schemes_m through the addParameterList
	function. Right now, relationToReturn doesn't have a populated vector<Parameter> parameterList_m set for it's header_m datamember.
	What we do below will fill that up for us.*/
	Scheme newHeader;
	newHeader = header_m.setParameterListForRenameFunctionLab4(parametersThatAreIDs);
	relationToReturn.setHeader(newHeader);

	return relationToReturn;
}

Scheme Relation::combineSchemes(vector<Relation> relationsFromPredicates) {
	size_t numSchemesToCombine;
	numSchemesToCombine = relationsFromPredicates.size();

	Scheme schemeOfNewRelation;
	vector<Parameter> parameterListForNewRelation;

	if (numSchemesToCombine == 1) {
		parameterListForNewRelation =
			relationsFromPredicates.at(0).getHeader().getParameterList();
	}
	else {
		parameterListForNewRelation =
			relationsFromPredicates.at(0).getHeader().getParameterList();
		//^^^POOP could be this
		for (size_t i = 0; i < numSchemesToCombine; i++) {

			if (i != 0) {
				Scheme schemeFromRelation;
				schemeFromRelation =
					relationsFromPredicates.at(i).getHeader();
				vector<Parameter> parameterListFromCurrentScheme = schemeFromRelation.getParameterList();


				for (size_t j = 0; j < parameterListFromCurrentScheme.size(); j++) {
					Parameter currentParam1 = parameterListFromCurrentScheme.at(j);

					size_t sizeOfParameterListForNewRelation = parameterListForNewRelation.size();

					for (size_t k = 0; k < sizeOfParameterListForNewRelation; k++) {
						bool addParameter = true;
						Parameter currentParam2 = parameterListForNewRelation.at(k);
						bool valuesMatch = false;

						if (currentParam1.getValue() == currentParam2.getValue()) {
							valuesMatch = true;
						}
						//if both true, then don't add. Else add
						if (valuesMatch) { k = sizeOfParameterListForNewRelation; }
						if ((k == parameterListForNewRelation.size() - 1) && addParameter) { //bool addParameter is true...
							parameterListForNewRelation.push_back(currentParam1);
						} //Add param to new paramList in the new scheme
					}
				}
			}
		}
	}

	//Now set the new paramList we have for the new scheme we will return
	schemeOfNewRelation.addParameterList(parameterListForNewRelation);
	return schemeOfNewRelation;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, Scheme s1, Scheme s2, Scheme newSchemeForRelation) {
	Tuple newTuple;
	vector<string> columnIndexFromNewScheme; //For colum indexes already added

	for (size_t i = 0; i < newSchemeForRelation.getParameterList().size(); i++) {
		bool alreadyFoundIt = false;
		string match = newSchemeForRelation.getParameterList().at(i).getValue();

		//Is the column head we need in s1?
		for (size_t j = 0; j < s1.getParameterList().size(); j++) {
			string valueFromS1 = s1.getParameterList().at(j).getValue();
			if (valueFromS1 == match) {
				//Yes, the column head we need is in s1, so add it to the newTuple
				string addMe = t1.getElementFromTupleList(j);
				newTuple.addToTupleList(addMe);
				j = s1.getParameterList().size(); //Escape this scheme because we found it
				alreadyFoundIt = true;
			}
		}

		if (!alreadyFoundIt) {
			//Is the column head we need in s2?
			for (size_t j = 0; j < s2.getParameterList().size(); j++) {
				string valueFromS2 = s2.getParameterList().at(j).getValue();
				if (valueFromS2 == match) {
					//Yes, the column head we need is in s1, so add it to the newTuple
					string addMe = t2.getElementFromTupleList(j);
					newTuple.addToTupleList(addMe);
					j = s2.getParameterList().size(); //Escape this scheme because we found it
				}
			}
		}
	}

	//New Tuple has been created
	return newTuple;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, Scheme s1, Scheme s2) {
	vector<Parameter> matchingColumns;
	vector<size_t> s1_columnIndex;
	vector<size_t> s2_columnIndex;

	//Find the matching columns
	for (size_t i = 0; i < s1.getParameterList().size(); i++) {
		for (size_t j = 0; j < s2.getParameterList().size(); j++) {
			string p1 = s1.getParameterList().at(i).getValue();
			string p2 = s2.getParameterList().at(j).getValue();
			if (p1 == p2) {
				matchingColumns.push_back(s1.getParameterList().at(i));
				s1_columnIndex.push_back(i);
				s2_columnIndex.push_back(j);
			}
		}
	}

	if (matchingColumns.size() == 0) { return true; } //No matches so just join away!

	//Now, with the matching columns we will combine the tuples
	for (size_t i = 0; i < matchingColumns.size(); i++) {
		//Are the tuple values the same?
			//Yes, do nothing
			//No, return false
		string temp1 = t1.getElementFromTupleList(s1_columnIndex.at(i));
		string temp2 = t2.getElementFromTupleList(s2_columnIndex.at(i));

		if (temp1 != temp2) {
			return false;
		}
	}

	//Now we are at the end and we have worked through everything and it is all chill to join.
	return true;
}

Relation Relation::projectNewRelation(Relation newEmptyRelation, vector<size_t> parameterPositionsWeCareAboutFromNewScheme, 
	vector<Parameter> columnsWeNeed, string columnsWeNeedAsString) {
	vector<Parameter> columns = newEmptyRelation.getHeader().getParameterList();
	Relation cleanedRelation;

	//Cleaning up the tuples in the columns we don't need
	set<Tuple> tuplesOfRelation = newEmptyRelation.getTuples();
	//How the tuples are structured
		/*
			Relation
				tuples_m
					tuples_m:: each index in the tuple matches with the scheme header
		*/
	for (Tuple t1 : tuplesOfRelation) {
		Tuple cleanedTuple;
		for (size_t i = 0; i < parameterPositionsWeCareAboutFromNewScheme.size(); i++) {
			for (size_t j = 0; j < columns.size(); j++) {
				if (columns.at(j).getValue() == columnsWeNeed.at(i).getValue()) {
					//We found a column that we care about!
					cleanedTuple.setRelationName(columnsWeNeedAsString);
					//For the rename part of all of this ^^^^
					cleanedTuple.addToTupleList(t1.getElementFromTupleList(j));
				}
			}
		}
		cleanedRelation.addTuple(cleanedTuple);
	}
	//Tuples are now cleaned and columns re-ordered

	//This is all renaming stuff below
	cleanedRelation.setRelationName(columnsWeNeedAsString);
	Scheme tempScheme;
	tempScheme.addParameterList(columnsWeNeed);
	cleanedRelation.setHeader(tempScheme);

	return cleanedRelation;
}

void Relation::printTuplesLab4(vector<string> parametersThatAreIDs, size_t numTuples) {

	set<Tuple>::iterator tupleIterator = tuples_m.begin();

	for (size_t i = 0; i < tuples_m.size(); i++) {

		Tuple tempTuple = *tupleIterator;
		size_t numTuplesOutputted = 0;

		for (size_t j = 0; j < tempTuple.getTupleListSize(); j++) {
			printTuplesForTempTupleLab4(parametersThatAreIDs, tempTuple, j, numTuplesOutputted);
		}
		tupleIterator++;
	}
}

void Relation::printTuplesForTempTupleLab4(vector<string>& parametersThatAreIDs, Tuple& tempTuple,
	size_t& j, size_t& numTuplesOutputted) {

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
		printSingleTupleWithSpaceLab4(tempTuple, tempColumn, j, parametersThatAreIDs);
	}
	else {

		/* lastColumnAsIndex is set to parametersthatareids.size() - 1 because we need to work with vectors which
		  are zero based*/
		size_t lastColumnAsIndex = parametersThatAreIDs.size() - 1;

		if (numTuplesOutputted == lastColumnAsIndex) {
			//if we are at the last item in our row and at the final column
			printSingleTupleWithNoSpaceLab4(tempTuple, tempColumn, j, parametersThatAreIDs, numTuplesOutputted);
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

void Relation::printSingleTupleWithSpaceLab4(Tuple tempTuple, size_t tempColumn, size_t j,
	vector<string> parametersThatAreIDs) {
	if ((j == tempTuple.getTupleListSize() - 1)) {
		cout << "  " << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j);
	}
	else {
		cout << "  " << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << endl;
	}
}

void Relation::printSingleTupleWithNoSpaceLab4(Tuple tempTuple, size_t tempColumn, size_t j,
	vector<string> parametersThatAreIDs, size_t& numTuplesOutputted) {
	/*if ((j == tempTuple.getTupleListSize() - 1)) {
		cout << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j);
	}
	else {*/
	cout << parametersThatAreIDs.at(tempColumn) << "=" << tempTuple.getElementFromTupleList(j) << endl;
	/*}*/
	numTuplesOutputted = 0; // Set numOutputted to zero so we can start printing for a new row	
}