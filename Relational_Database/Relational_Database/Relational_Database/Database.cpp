#include "Database.h"

Database::Database(vector<Predicate> schemes, vector<Predicate> facts, vector<Predicate> queries) {
	this->schemes_m = schemes;
	this->facts_m = facts;
	this->queries_m = queries;

	/*cout << "queries_m: ";
	for (size_t i = 0; i < queries_m.size(); i++) {
		cout << queries_m.at(i).toString() << " ";
	}
	cout << endl << endl;
*/
	//-----------------------------Handling the schemes (adding the tuples)--------------------------------//
	/*Schemes are lists of attribute names. So by iterating through the schemes vector, we are adding column
	headings to all of the realtions (aka tables) in the database*/
	for (size_t i = 0; i < schemes.size(); i++) {
		Relation relationToAddToDatabase;
		string relationName = schemes.at(i).getId();

		Scheme headerToAddToRelation;
		headerToAddToRelation.addParameterList(schemes.at(i).getVectorOfParameters());

		//Now set the relation (aka table) information for our database
		relationToAddToDatabase.setHeader(headerToAddToRelation);
		relationToAddToDatabase.setRelationName(relationName);

		addRelation(relationToAddToDatabase);
	}

	//-----------------------------Handling the facts (adding the tuples)--------------------------------//
	/*Facts are what hold the weird string things (like 'Snoopy' or '1234'. So to 
	populate the vector of strings for our Tuple class, we need to get each item in our 
	facts vector(which is found in 	our datalogProgram class).Each position in our facts 
	vector holds all of the strings (or tuple values) for a row in our table(aka relation)*/
	for (size_t i = 0; i < facts_m.size(); i++) {
		Tuple tupleObj;

		string factName = facts_m.at(i).getId(); /*This gets the factName which is also the table name (aka relation name). These
												 names can be different. When they are different, that just means that we are adding
												 different rows to different tables (aka relations) and we don't have to worry about
												 adding ALL rows to ONE table at a time*/
		tupleObj.setRelationName(factName); //Now the table name for the row being added has been noted

		vector<Parameter> cellValuesInRow = this->facts_m.at(i).getVectorOfParameters();
		/*^^^This vector<Parameter> is full of strings. What we are going to do below is
		basically transfer all of the strings from this vector<Parameter> to our vector<string>
		so we can use that for our data member called tupleList_m in our Tuple class.*/

		vector<string> cellValuesInRowForTupleClass;

		for (size_t j = 0; j < cellValuesInRow.size(); j++) {
			string individualValueOfCellInRow = cellValuesInRow.at(j).getValue();
			cellValuesInRowForTupleClass.push_back(individualValueOfCellInRow);
		}

		//tupleObj.tupleList_m = cellValuesInRowForTupleClass;
		tupleObj.setTupelList(cellValuesInRowForTupleClass); /*Now we have moved over all of the values in the
															 row over to the tuple class. So now all of the
															 values for that specific row in the table (aka
															 relation) are stored away*/
		addRowToRelation(tupleObj); /*Now we have processed one element in our facts vector. The for loop will now
									increment and add another row to a relation (aka table)*/
	}
}

void Database::addRelation(Relation relationObj) {
	string relationName = relationObj.getRelationName();
	relationMap_m.insert(pair<string,Relation>(relationName, relationObj)); /*This will insert our new relation
																						   (aka table) into our databse. This also 
																						   prevents duplicates from being added.*/
}

void Database::addRowToRelation(Tuple tupleObj) {
	//TupleObj is a tuple object that has a relation name and a vector<string> of tuple values (values for each position in the row)
	string relationName = tupleObj.getRelationName(); //Get name of table/relation
	Relation relationIterator = relationMap_m.find(relationName)->second; /*This sets relationIterator to the position of the current
																		relation in the map. This relation definintely already exists*/
	relationIterator.addTuple(tupleObj); /*Updates the value in the map (the value is a relation) by
										 Adding another tuple (aka row of values (aka vector<string>)) to the relation (aka table)*/
	relationMap_m.at(relationName) = relationIterator; /*Now we are adding the updated value (aka relation) back into the map
													 so the current relation is up to date.*/

}

void Database::evaluateQueries() {
	Relation tempRelation;
	for (size_t i = 0; i < queries_m.size(); i++) {
		
		//Give the tempRelation a name
		string tempRelationName = queries_m.at(i).getId(); 
		
		/*Get the parameters in the temp relation. If the query was "SK(A,'c')" then the parameters would be "A,'c'"*/
		vector<Parameter> parametersFromTempRelation = queries_m.at(i).getVectorOfParameters();

		//Find the current relation that our query is asking for in our map of relations and set it to foundRelation
		Relation foundRelation = relationMap_m.find(tempRelationName)->second;
		tempRelation = foundRelation; //Set the relations to each other.

		//Loop through the parameters in our tempRelation.
		//If the query was "SK(A,'c')" then the parameters in our tempRelation would be "A,'c'"* /
		for (size_t j = 0; j < parametersFromTempRelation.size(); j++) {

			//Get the parameter type and the parameter value
			/*cout << "We are in queries_m.at(" << i << ")" << endl;
			cout << "We are in parametersFromTempRelation.at(" << j << ")" << endl << endl;*/
			string parameterType = parametersFromTempRelation.at(j).getType();
			string parameterValue = parametersFromTempRelation.at(j).getValue();
			size_t positionInParameterVector = j;

			if (parameterType == "ID") {

				bool duplicateParameterExists = false;
				size_t positionOfDuplicateParameter;

				for (size_t k = 0; k < parametersThatAreIDs_m.size(); k++) {

					if (parametersThatAreIDs_m.at(k) == parameterValue) {
						duplicateParameterExists = true;
						positionOfDuplicateParameter = k;
						break;
					}
				}

				if (duplicateParameterExists) {
					tempRelation.select(positionOfDuplicateParameter, positionInParameterVector);
				}
				else {
					//Push ID into vector parametersThatAreIDs_m and push positioInParameterVector into vector parameterPositions_m
					parametersThatAreIDs_m.push_back(parameterValue); /*parameterValue is an ID like "A". So in our example query of
																	  "SK(A,'c')", "A" would be an ID that would be added here and
																	  'c' would be added in the STRING elseif part of this if statement*/
					parameterPositions_m.push_back(positionInParameterVector);
				}			
			}
			else if (parameterType == "STRING") {
				tempRelation = tempRelation.select(positionInParameterVector, parameterValue);
			}
		}

		tempRelation = tempRelation.project(parameterPositions_m);

		tempRelation = tempRelation.rename(parametersThatAreIDs_m);

		//Pring the query. I. e. Make "SK(A,'c') print as SK(A,'c')? Yes(2)"
		//cout << "THIS WORK? (Printing from Database.cpp class)" << endl << endl;
		cout << tempRelation.getRelationName() << "(";

		ostringstream oss;
		for (size_t z = 0; z < parametersFromTempRelation.size(); z++) {
			if (parametersFromTempRelation.size() - 1 == z) {
				oss << parametersFromTempRelation.at(z).getValue();
			}
			else {
				oss << parametersFromTempRelation.at(z).getValue() << ",";
			}
		}

		cout << oss.str() << ")? ";
		if (tempRelation.getNumTuples() > 0) {
			cout << "There are more than one tuple here" << endl;
		}
		else {
			cout << "No" << endl;
		}

		//Print the tuples (values in the row) in the query involved

		//Clear the vectors that we populated with the tempRelation
		parametersThatAreIDs_m.clear();
		parameterPositions_m.clear();


	}
}	