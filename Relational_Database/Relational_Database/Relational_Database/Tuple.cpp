#include "Tuple.h"

string Tuple::toString() {
	ostringstream oss;
	for (unsigned i = 0; i < this->size(); i++) {
		oss << this->at(i) << endl;
	}
	return oss.str();
}

void Tuple::setTupelList(vector<string> tupleList) {
	this->tupleList_m = tupleList;
}

string Tuple::getElementFromTupleList(size_t positionInTupleList) {
	return tupleList_m.at(positionInTupleList);
}

void Tuple::addToTupleList(string tupleValueToAdd) {
	this->tupleList_m.push_back(tupleValueToAdd);
}