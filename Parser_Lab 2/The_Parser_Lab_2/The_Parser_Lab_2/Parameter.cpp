#include "Parameter.h"

Parameter::Parameter(string type, string value) {
	this->type_m = type; //Needed for later calculations, even though it won't be returned.
	this->value_m = value; //To be returned in the toString function
}

string Parameter::toString() { 
	//They only want the value from the Parameter
	return this->value_m;
}