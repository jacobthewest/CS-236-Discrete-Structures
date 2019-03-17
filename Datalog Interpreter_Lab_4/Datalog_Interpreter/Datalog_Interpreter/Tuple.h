#ifndef TUPLE_H
#define TUPLE_H


#include <iostream>
#include <vector>
#include <string>
#include <sstream>	// ostringstream


using namespace std;

class Tuple {

private:
	
	string relationName_m;
	vector<string> tupleList_m;
public:
		
	//Constructor
	Tuple() {};
	~Tuple() {};
	
	string toString();

	void setRelationName(string name) { this->relationName_m = name; }
	string getRelationName() { return this->relationName_m; }

	void setTupleList(vector<string> tupleList);	
	string getElementFromTupleList(size_t positionInTupleList);
	void addToTupleList(string tupleValueToAdd);
	size_t getTupleListSize() { return this->tupleList_m.size(); }

	bool operator< (const Tuple constTuple) const {
		return this->tupleList_m < constTuple.tupleList_m;
	}
};

#endif //TUPLE_H