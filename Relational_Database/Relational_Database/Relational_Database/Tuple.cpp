#include "Tuple.h"

string Tuple::toString() {
	ostringstream oss;
	for (unsigned i = 0; i < tupleList_m.size(); i++) {
		oss << tupleList_m.at(i) << endl;
	}
	return oss.str();
}

void Tuple::setTupleList(vector<string> tupleList) {
	this->tupleList_m = tupleList;
}

string Tuple::getElementFromTupleList(size_t positionInTupleList) {
	return tupleList_m.at(positionInTupleList);
}

void Tuple::addToTupleList(string tupleValueToAdd) {
	this->tupleList_m.push_back(tupleValueToAdd);
}