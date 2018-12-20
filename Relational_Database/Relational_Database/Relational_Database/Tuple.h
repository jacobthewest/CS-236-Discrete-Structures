#ifndef TUPLE_H
#define TUPLE_H


#include <iostream>
#include <vector>
#include <string>
#include <sstream>	// ostringstream


using namespace std;

class Tuple : public vector<string> {

private:
	
	string relationName_m;
public:

	vector<string> tupleList_m;
	//Constructor
	Tuple() {};
	~Tuple() {};
	
	string toString();

	void setRelationName(string name) { this->relationName_m = name; }
	string getRelationName() { return this->relationName_m; }

	void setTupelList(vector<string> tupleList);	
	string getElementFromTupleList(size_t positionInTupleList);
	void addToTupleList(string tupleValueToAdd);
};

#endif //TUPLE_H