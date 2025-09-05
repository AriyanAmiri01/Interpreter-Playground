#include "MyLexor.h"
// MyLexor.cpp
#include "MyLexor.h"


////////////////////////////////////////////////////////
/// LEXICAL ANALYSER STUFFS
MyLexor::MyLexor(std::string xFile)
{
	// Getting the file string and initializing the indentStack
	oss << xFile;
	S.push(0);
}

void  MyLexor::Tokenize(){
	// Just extra cheking of the stack just for the debug version
	#ifndef NDEBUG
	if(S.empty()){
		EXCEPT_INT("The laxer has failed to initialize its stack!");
	}
	#endif

	// Looping through each line
	while(std::getline(oss, line)){
		// Extracting Indentation
		int lineSize = static_cast<int>(line.size());

		// Ignoring empty lines
		if(line.empty()) {
			continue;
		}

		// Looping through each character until we see a char and add indent
		int i = 0;
		bool continueTrigger = false;
		for(i; i < lineSize; i++) {
			// checking the character
			if(!std::isspace(line.at(i))) {
				break;
			}
			// a new empty line so we exit out of loop a gen dedent
			if(i + 1 >= lineSize){
				continueTrigger = true;
			}
		}
		if(continueTrigger){ continue; }


		// Comparing this line indentation with the prev stack indentation
		if(i > S.top()){
			S.push(i);
			Token t(TOKEN_INDENT,"Indent", lineNum);
			tokens.push_back(t);
		}
		else if(i < S.top()){
			while(!S.empty() && i < S.top()){
				S.pop();
				Token t(TOKEN_DEDENT, "Dedent", lineNum);
				tokens.push_back(t);
			}
			if(S.empty() || i != S.top()) {
				std::cout << "i:" << i << "top:" << S.top();
				EXCEPT_INT("Something");
			}
		}

		// WE ARE FIXED WITH INDENTATION :: time to tokenize
		while(i < lineSize){
			// If It is a space
			if(i < lineSize && std::isspace(line.at(i))){
				i++;
			}
			//Start with alpha
			if(i < lineSize && std::isalpha(line.at(i))){

				std::string tempToken;
				tempToken += line.at(i);
				i++;
				while(i < lineSize && (std::isalnum(line.at(i)) || (line.at(i) == '_'))) {
					tempToken += line.at(i);
					i++;

				}
				if(keywordTrees::checkExistance(tempToken)){
					Token t(TOKEN_KEYWORD, tempToken, lineNum);
					tokens.push_back(t);
				}
				else{
					Token tempIdentifier(TOKEN_IDENTIFIER, tempToken, lineNum);
					tokens.push_back(tempIdentifier);
				}
			}

			// Start with a number
			if(i < lineSize && std::isdigit(line.at(i))){

				std::string tempToken;
				tempToken += line.at(i);
				i++;
				while(i < lineSize && std::isdigit(line.at(i))){
					tempToken += line.at(i);
					i++;

				}
				Token tempNumTok(TOKEN_NUMBER,tempToken, lineNum);
				tokens.push_back(tempNumTok);

				if(i < lineSize && std::isalpha(line.at(i))) {
					EXCEPT_INT("An alphabetical symbol immediately after a numerical token is not allowed");
				}
			}

			// Finding string liters
			if(i < lineSize && (line.at(i) == '"')){
				std::string tempToken;
				i++;
				while(i < lineSize && line.at(i) != '"'){

					tempToken += line.at(i);
					i++;
				}
				if(i >= lineSize && line.at(i) != '"'){
					EXCEPT_INT("There is second quotation mark for the string");
				}
				Token t(TOKEN_STRING, tempToken, lineNum);
				tokens.push_back(t);
			}

			// Finding the character literals
			if(i < lineSize && line.at(i) == '\'') {
				i++;
				if(i >= lineSize)
					EXCEPT_INT("Unexpected end of line after opening single quote");
				char c = line.at(i);
				i++;
				if(i >= lineSize || line.at(i) != '\'')
					EXCEPT_INT("Missing closing single quote for character literal");
				i++;
				Token t(TOKEN_STRING, std::string(1, c), lineNum);
				tokens.push_back(t);
			}

			// Start with an delimiter
			if(i < lineSize){
				switch(line.at(i))
				{
				case(':'):
					{
						Token Tok(TOKON_DOUBLECOLON,std::string(1, ':'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(';'):
					{
						Token Tok(TOKEN_SEMICOLON,std::string(1, ';'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(','):
					{
						Token Tok(TOKEN_COMMA,std::string(1, ','), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('.'):
					{
						Token Tok(TOKEN_DOT, std::string(1, '.'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('('):
					{
						Token Tok(TOKEN_OPENPARAN, std::string(1, '('), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(')'):
					{
						Token Tok(TOKEN_CLOSEPARAN, std::string(1, ')'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('{'):
					{
						Token Tok(TOKEN_OPENBARAC ,std::string(1, '{'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('}'):
					{
						Token Tok(TOKEN_CLOSEBARAC, std::string(1, '}'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('<'):
					{
						i++;
						if(i < lineSize && line.at(i) == '<'){

							Token t(TOKEN_LOWEREQUAL,std::string(1, '='), lineNum);
							tokens.push_back(t);
							i++;

						}
						else{
							Token t(TOKEN_LOWER, std::string(1, '<'), lineNum);
							tokens.push_back(t);
						}
						break;
					}
				case('>'):
					{
						i++;
						if(i < lineSize && line.at(i) == '>'){
							Token t(TOKEN_BIGGEREQUAL,std::string(1, '='), lineNum);
							tokens.push_back(t);
							i++;
						}
						else{
							Token t( TOKEN_BIGGER,std::string(1, '>'), lineNum);
							tokens.push_back(t);
						}
						break;
					}
				case('='):
					{
						i++;
						if(i < lineSize && line.at(i) == '='){
							Token t(TOKEN_CHECKEQUAL,"==", lineNum);
							tokens.push_back(t);
							i++;
						}
						else{
							Token t(TOKEN_EQUAL ,std::string(1, '='), lineNum);
							tokens.push_back(t);
						}
						break;
					}
				case('%'):
					{
						Token Tok(TOKEN_MODULE,std::string(1, '%'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('+'):
					{
						Token Tok(TOKEN_PLUS, std::string(1, '+'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('-'):
					{
						Token Tok(TOKEN_MINUS, std::string(1, '-'), lineNum);
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('*'):
					{
						i++;
						if(i < lineSize && line.at(i) == '*'){
							Token t(TOKEN_EXPONENTIAL, "**", lineNum);
							tokens.push_back(t);
							i++;
						}
						else{
							Token Tok(TOKEN_MULTIPLICATION,std::string(1, '*'), lineNum);
							tokens.push_back(Tok);
						}
						break;
					}
					
				case('/'):
					{
						i++;
						if(i < lineSize && line.at(i) == '/'){
							Token t(TOKEN_FLOORDIVISION,"//", lineNum);
							tokens.push_back(t);
							i++;
						}
						else{
							Token Tok(TOKEN_DEVISION, std::string(1, '/'), lineNum);
							tokens.push_back(Tok);
						}
						break;
					}
				case('!'):
					{
						i++;
						if(line.at(i) == '='){
							Token t(TOKEN_NCHECKEQUAL ,"!=", lineNum);
							tokens.push_back(t);
							i++;
						}
						else{
							Token Tok(TOKEN_NOT, std::string(1, '!'), lineNum);
							tokens.push_back(Tok);
						}
						break;
					}

				case(' '):
					{
						i++;
						break;
					}
				default:
					{
						EXCEPT_INT("The python code contains a symbol that is not defined in the grammer");
						i++;
						break;
					}
				}
			}
		}

		Token t(TOKEN_NEWLINE, "NewLine", lineNum);
		tokens.push_back(t);
	}
	while(S.size() > 1) { // We assume base indentation is 0 at bottom of stack
		S.pop();
		tokens.push_back(Token(TOKEN_DEDENT, "Dedent", lineNum));
	}
	Token t(TOKEN_EOF, "EndOfFileMarker", lineNum);
	tokens.push_back(t);
}


////////////////////////////////////////////////////////
/// GETTERS
std::vector<Token> MyLexor::getTokens()
{
	return std::vector<Token>(tokens);
}


////////////////////////////////////////////////////////
/// TEST STUFFS
void MyLexor::testTokens()
{
	// Defining a basic function for seeing the result of the lexor
	std::cout
		<< std::endl
		<< "___________________________________"
		<< "The result of the testTokens:" << std::endl;
	int i = 0;
	for(auto t : tokens){
		if(t.getTokenID() == TOKEN_NEWLINE){
			std::cout << "[" << t.getTokenString() << "]" << std::endl;
			i++;
		}
		else{
			std::cout << "[" << t.getTokenString() << "]";
			i++;
		}
	}
	std::cout 
		<< "___________________________________" 
		<< std::endl;
}