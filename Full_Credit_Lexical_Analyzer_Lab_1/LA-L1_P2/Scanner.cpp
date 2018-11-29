#include "Scanner.h"

char Scanner::advance() {
	currentChar_m = fileStream_m.get(); //Get the next char
										//setCurrentType(currentChar_m); //Set the type of the current char
	charLocation_m++;
	return currentChar_m;
}

void Scanner::openFile(string fileName) {
	fileStream_m.open(fileName); //open file
	currentChar_m = fileStream_m.get(); //get first char
}

bool Scanner::checkIfActualKeyword(string &valueSoFar) {

	while (checkIfCurrentCharIsCompatibleWithIDState(currentChar_m)) {
		valueSoFar += currentChar_m;
		advance();
	}
	if (valueSoFar == "Schemes" || valueSoFar == "Facts" || valueSoFar == "Queries" || valueSoFar == "Rules") {
		//The word we were checking IS an actual keyword
		return true;
	}
	else {
		//The word we were checking IS NOT an actual keyword
		return false;
	}

}

bool Scanner::checkIfCurrentCharIsCompatibleWithIDState(char characterToCheck) {
	switch (characterToCheck) {
	case '.':
	case ',':
	case '?':
	case '(':
	case ')':
	case ':':
	case '+':
	case '*':
	case '#':
	case '\'':
	case ' ':
	case '\n':
	case -1:
		return false;
		break;
	default:
		return true;
		break;
	}
}
bool checkIfNextCharIsCompatibleWithStringState(char nextCharacter) {
	switch (nextCharacter) {
	case '.':
	case ',':
	case '?':
	case '(':
	case ')':
	case ':':
	case '+':
	case '*':
	case '#':
	case '\'':
	case ' ':
	case '\n':
	case -1:
		return false;
		break;
	default:
		return true;
		break;
	}
}
void Scanner::setCurrentTypeForSingleCharacter(char singleCharacter) {
	switch (singleCharacter) {
	case '.':
		currentType_m = PERIOD;
		break;
	case ':':
		currentType_m = COLON;
		break;
	case ',':
		currentType_m = COMMA;
		break;
	case '?':
		currentType_m = Q_MARK;
		break;
	case '(':
		currentType_m = LEFT_PAREN;
		break;
	case ')':
		currentType_m = RIGHT_PAREN;
		break;
	case '+':
		currentType_m = ADD;
		break;
	case '*':
		currentType_m = MULTIPLY;
		break;
	default:
		currentType_m = ERROR;
		break;
	}
}