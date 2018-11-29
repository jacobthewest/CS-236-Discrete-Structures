#include "Parameter.h"

Parameter::Parameter(string type, string value) {
	this->type_m = type;
	this->value_m = value;
}

string Parameter::toString() {
	return this->value_m;
}