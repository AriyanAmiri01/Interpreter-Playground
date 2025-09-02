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
	if(S.empty()){
		S.push(0);
	}
	// Looping through each line
	while(std::getline(oss, line)){

		// Extracting Indentation
		int lineSize = static_cast<int>(line.size());
		int i = 0;

		// Ignoring empty lines
		if(line.empty()) {
			continue;
		}
		bool continueTrigger = false;
		for(i; i < lineSize; i++) {
			if(!std::isspace(line.at(i))) {
				break;
			}
			if(i + 1 >= lineSize){
				continueTrigger = true;
			}
		}
		if(continueTrigger){ continue; }


		// Comparing this line indentation with the prev stack indentation
		if(i > S.top()){
			S.push(i);
			indentTok t("Indent");
			tokens.push_back(t);
		}
		else if(i < S.top()){
			while(!S.empty() && i < S.top()){
				S.pop();
				dedentTok t("Dedent");
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
					keywordTok t(tempToken);
					tokens.push_back(t);
				}
				else{
					identifierTok tempIdentifier(tempToken);
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
				numericalTok tempNumTok(tempToken);
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
				stringTok t(tempToken);
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
				charTok t(std::string(1, c));
				tokens.push_back(t);
			}

			// Start with an delimiter
			if(i < lineSize){
				switch(line.at(i))
				{
				case(':'):
					{
						punctuationTok Tok(std::string(1, ':'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(';'):
					{
						punctuationTok Tok(std::string(1, ';'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(','):
					{
						punctuationTok Tok(std::string(1, ','));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('.'):
					{
						punctuationTok Tok(std::string(1, '.'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('('):
					{
						delimiterTok Tok(std::string(1, '('));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case(')'):
					{
						delimiterTok Tok(std::string(1, ')'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('{'):
					{
						delimiterTok Tok(std::string(1, '{'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('}'):
					{
						delimiterTok Tok(std::string(1, '}'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('<'):
					{
						i++;
						if(i < lineSize && line.at(i) == '<'){

							operatorTok t(std::string(1, '='));
							tokens.push_back(t);
							i++;

						}
						else{
							operatorTok t(std::string(1, '<'));
							tokens.push_back(t);
						}
						break;
					}
				case('>'):
					{
						i++;
						if(i < lineSize && line.at(i) == '>'){
							operatorTok t(std::string(1, '='));
							tokens.push_back(t);
							i++;
						}
						else{
							operatorTok t(std::string(1, '>'));
							tokens.push_back(t);
						}
						break;
					}
				case('='):
					{
						i++;
						if(i < lineSize && line.at(i) == '='){
							operatorTok t("==");
							tokens.push_back(t);
							i++;
						}
						else{
							operatorTok t(std::string(1, '='));
							tokens.push_back(t);
						}
						break;
					}
				case('%'):
					{
						operatorTok Tok(std::string(1, '%'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('+'):
					{
						operatorTok Tok(std::string(1, '+'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('-'):
					{
						operatorTok Tok(std::string(1, '-'));
						tokens.push_back(Tok);
						i++;
						break;
					}
				case('*'):
					{
						i++;
						if(i < lineSize && line.at(i) == '*'){
							operatorTok t("**");
							tokens.push_back(t);
							i++;
						}
						else{
							operatorTok Tok(std::string(1, '*'));
							tokens.push_back(Tok);
						}
						break;
					}
				case('^'):
					{
						operatorTok t("^");
						tokens.push_back(t);
						i++;
						break;
					}
				case('/'):
					{
						i++;
						if(i < lineSize && line.at(i) == '/'){
							operatorTok t("//");
							tokens.push_back(t);
							i++;
						}
						else{
							operatorTok Tok(std::string(1, '/'));
							tokens.push_back(Tok);
						}
						break;
					}
				case('!'):
					{
						i++;
						if(line.at(i) == '='){
							operatorTok t("!=");
							tokens.push_back(t);
							i++;
						}
						else{
							operatorTok Tok(std::string(1, '!'));
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

		newLineTok t("NewLine");
		tokens.push_back(t);
	}
	while(S.size() > 1) { // We assume base indentation is 0 at bottom of stack
		S.pop();
		tokens.push_back(dedentTok("Dedent"));
	}
	endOfFileTok t("EndOfFileMarker");
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