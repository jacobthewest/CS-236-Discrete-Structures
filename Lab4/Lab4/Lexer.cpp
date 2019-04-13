#include "Lexer.h"

using namespace std;

Lexer::Lexer(string fileName) {
	scanner.openFile(fileName);
	currentState = START_STATE; //set to start state
	endOfProgram_NowWePrint_m = false;
	startTheProgram(); //Call the startTheProgram function
}

void Lexer::startTheProgram() {
	while (!endOfProgram_NowWePrint_m) {
		switch (currentState) {
		case START_STATE:
			startState();
			break;
		case SINGLE_CHARACTER_STATE:
			singleCharacterState();
			break;
		case STRING_START_STATE:
			stringStartState();
			break;
		case STRING_END_STATE:
			stringEndState();
			break;
		case ID_STATE:
			idState();
			break;
		case SINGLE_LINE_COMMENT_STATE:
			singleLineCommentState();
			break;
		case MULTI_LINE_COMMENT_STATE:
			multiLineCommentState();
			break;
		case END_OF_FILE_STATE:
			endOfFileState();
			break;
		case COLON_DASH_STATE:
			colonDashState();
			break;
		case WHITESPACE_STATE:
			whitespaceState();
			break;
		default: //UNDEFINED_STATE
			undefinedState();
			break;
		}
	}
}


void Lexer::startState() {
	valueSoFar = "";
	switch (scanner.getCurrentChar()) {
	case '.':
	case ',':
	case '?':
	case '(':
	case ')':
	case '+':
	case '*':
		currentState = SINGLE_CHARACTER_STATE;
		break;
	case ':':
		if (scanner.peek() == '-') { currentState = COLON_DASH_STATE; }
		else { currentState = SINGLE_CHARACTER_STATE; }
		break;
	case '#':
		scanner.setCurrentTypeToComment();
		if (scanner.peek() == '|') { currentState = MULTI_LINE_COMMENT_STATE; }
		else { currentState = SINGLE_LINE_COMMENT_STATE; }
		break;
	case '\'':
		currentState = STRING_START_STATE;
		break;
	case '\n':
		scanner.incrementLineNumber();
		scanner.advance();
		break;
	case '\r':
		scanner.incrementLineNumber();
		scanner.advance();
		break;
	case ' ':
		currentState = WHITESPACE_STATE;
		break;
	case '\t':
		scanner.advance();
		currentState = START_STATE;
		break;
	case -1:
		currentState = END_OF_FILE_STATE;
		break;
	default:
		if (isalpha(scanner.getCurrentChar())) { currentState = ID_STATE; }
		else { currentState = UNDEFINED_STATE; }
		break;
	}
}

void Lexer::singleCharacterState() {
	//CurrentChar is a single character
	valueSoFar += scanner.getCurrentChar(); //Append to valueSoFar
	scanner.setCurrentTypeForSingleCharacter(scanner.getCurrentChar());
	scanner.tokenize(valueSoFar);
	scanner.advance();
	currentState = START_STATE;
}

void Lexer::undefinedState() {
	//CurrentChar is the undefined character/problem
	scanner.setCurrentTypeToUndefined();
	currentState = START_STATE;
	switch (scanner.getCurrentChar()) {
	case -1: //Used for undefined strings
			 //valueSoFar.pop_back(); //Comment out for windows
		scanner.tokenizeSpecial(valueSoFar);
		//scanner.decrementLineNumber(); //comment out for windows
		break;
	default:
		valueSoFar += scanner.getCurrentChar();
		scanner.tokenize(valueSoFar);
		scanner.advance();
		break;
	}
}
void Lexer::idState() {
	//Current Char is a-z or A-Z
	//An approved character, now we need to see if it is a Scheme, Fact, Query, or Rule. If not, then do something.

	if (scanner.checkIfActualKeyword(valueSoFar)) {
		//The word IS a keyword
		setKeywordType(valueSoFar); //Set the keyword Type
		scanner.tokenize(valueSoFar);
		currentState = START_STATE;
	}
	else {
		//The word IS NOT a keyword
		scanner.setCurrentTypeToID(); //Create an ID
		while (scanner.checkIfCurrentCharIsCompatibleWithIDState(scanner.getCurrentChar())) {
			valueSoFar += scanner.getCurrentChar();
			scanner.advance();
		}
		scanner.tokenize(valueSoFar);
		currentState = START_STATE;
	}
}

void Lexer::endOfFileState() {
	scanner.setCurrentTypeToEndOfFile();
	scanner.tokenize(valueSoFar);
	endOfProgram_NowWePrint_m = true;
}

void Lexer::colonDashState() {
	scanner.setCurrentTypeColonDash();
	//Make sure to append the : first
	valueSoFar += scanner.getCurrentChar();
	scanner.advance();
	valueSoFar += scanner.getCurrentChar(); //'-' has been appended
	scanner.advance();
	currentState = START_STATE;
	scanner.tokenize(valueSoFar);
	//Now the :- have been appended. CurrentChar is '-'
}

void Lexer::singleLineCommentState() {
	//CommentType has already been set
	//CurrentChar is # 
	valueSoFar += scanner.getCurrentChar();
	while (scanner.peek() != -1 && scanner.peek() != '\n') { scanner.advance(); valueSoFar += scanner.getCurrentChar(); }
	//The next char is either a -1 or a \n
	scanner.advance(); //Currerntchar is now -1 or \n
					   //tokenize(); //Don't add Comments to the Vector. This change is for lab 2
	switch (scanner.getCurrentChar()) {
	case -1:
		currentState = END_OF_FILE_STATE;
		break;
	default: //currentChar is for sure the \n
		currentState = START_STATE;
		break;
	}
}
void Lexer::multiLineCommentState() {
	//CommentType has already been set
	//Make sure to append the # first
	scanner.setStringStartedOnThisLineNumber(scanner.getCurrentLineNumber());
	valueSoFar += scanner.getCurrentChar(); //# has done been appended boi'!
	scanner.advance(); //Currentchar is now '|'
	valueSoFar += scanner.getCurrentChar(); //'|' has been appended
	bool bStayInThisLoop = true;
	while (scanner.peek() != -1 && bStayInThisLoop) {
		scanner.advance();
		valueSoFar += scanner.getCurrentChar();
		if (scanner.getCurrentChar() == '|' && scanner.peek() == '#') {
			//The '|' has been appended
			scanner.advance(); //CurrentChar is now '#'
			valueSoFar += scanner.getCurrentChar(); //The '#' has been appended
													//tokenize(scanner.getStringStartedOnThisLineNumber()); //Don't add Comments to the Vector. This change is for lab 2
			scanner.advance(); //Now the currentchar should be a \n
			currentState = START_STATE;
			bStayInThisLoop = false;
		}
		else if (scanner.getCurrentChar() == '\n') { scanner.incrementLineNumber(); }
	}
	endOfMultiLineCommentOrEndOfFileIsTrue();
}

void Lexer::stringStartState() {
	scanner.setCurrentTypeToString(); //Set type
	valueSoFar += scanner.getCurrentChar(); //append
	if (scanner.getFirstTimeInStringStartStateBool()) {
		scanner.setStringStartedOnThisLineNumber(scanner.getCurrentLineNumber());
	}
	while (scanner.peek() != '\'' && scanner.peek() != -1) {
		scanner.advance();
		valueSoFar += scanner.getCurrentChar();
		if (scanner.getCurrentChar() == '\n') { scanner.incrementLineNumber(); }
	}

	scanner.advance(); //Current char is now '\'' or -1
	switch (scanner.getCurrentChar()) {
	case -1:
		currentState = UNDEFINED_STATE;
		break;
	default: //for sure the '\'' or new line
		valueSoFar += scanner.getCurrentChar();
		currentState = STRING_END_STATE;
		break;
	}

}

void Lexer::stringEndState() {
	if (scanner.peek() == '\'') {
		scanner.advance();
		currentState = STRING_START_STATE;
		scanner.setfirstTimeInStringStartStateBool(false);
	}
	else {
		scanner.advance(); //Make current char NOT be '\''
		scanner.tokenizeSpecial(valueSoFar);
		scanner.setfirstTimeInStringStartStateBool(true);
		switch (scanner.getCurrentChar()) {
		case ' ':
			currentState = WHITESPACE_STATE;
			break;
		case -1:
			currentState = END_OF_FILE_STATE;
			break;
		default:
			currentState = START_STATE;
			break;
		}
	}
}

void Lexer::setKeywordType(string valueSoFarForThisFunction) {

	if (valueSoFarForThisFunction == "Schemes") { scanner.setCurrentTypeToSchemes(); }
	else if (valueSoFarForThisFunction == "Facts") { scanner.setCurrentTypeToFacts(); }
	else if (valueSoFarForThisFunction == "Rules") { scanner.setCurrentTypeToRules(); }
	else {/*It's ok, this will for sure be queries*/ scanner.setCurrentTypeToQueries(); }
}

void Lexer::whitespaceState() {
	scanner.advance();
	currentState = START_STATE;
}

void Lexer::endOfMultiLineCommentOrEndOfFileIsTrue() {
	if (scanner.getCurrentChar() == '\n' && scanner.peek() == -1) { //This will always be true
		scanner.incrementLineNumber();
		scanner.advance();
		if (scanner.getCurrentChar() == '\n') { currentState = START_STATE; }
		else { scanner.decrementLineNumber(); currentState = UNDEFINED_STATE; }
	}
}

string Lexer::getTokenTypeAsString(Token token) {
	return token.getTokenTypeAsString(token);
}