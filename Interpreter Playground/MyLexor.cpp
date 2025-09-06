// MyLexor.cpp
#include "MyLexor.h"



////////////////////////////////////////////////////////
/// LEXICAL ANALYSER STUFFS
MyLexor::MyLexor(std::string xFile)
{
	// Getting the file string and initializing the indentStack
	oss << xFile;

}

void  MyLexor::Tokenize(){
	// Creating the stach for the indentations
	std::stack<int> S;
	S.push(0);

	// Just extra cheking of the stack just for the debug version
	#ifndef NDEBUG
	if(S.empty()){
		EXCEPT_INT("The laxer has failed to initialize its stack!");
	}
	#endif

	// Looping through each line
	std::string line;
	int lineNum = 0;
	while(std::getline(oss, line)){
		// Extracting Indentation
		int lineSize = static_cast<int>(line.size());
		lineNum++;

		// Ignoring empty lines
		if(line.empty()) {
			continue;
		}

		// Skip completely empty or whitespace-only lines
		auto firstNonSpace = line.find_first_not_of(" \t");
		if(firstNonSpace == std::string::npos) {
			continue; // no token for blank lines
		}

		// Indentation count = index of first non-space
		int i = static_cast<int>(firstNonSpace);

		// Indent and dedent tokenization <TOKEN_INDENT> or <TOKEN_DEDENT>
		if(i > S.top()){
			S.push(i);
			tokens.push_back(Token(TOKEN_INDENT, "Indent", lineNum));
		}else if(i < S.top()){
			while(!S.empty() && i < S.top()){
				S.pop();
				Token t(TOKEN_DEDENT, "Dedent", lineNum);
				tokens.push_back(t);
			}
			#ifndef NDEBUG
			if(S.empty() || i != S.top()) {
				EXCEPT_INT("An error occured while trying to pop out an empty stack in the lexor");
			}	
			#endif
		}

		// Finished with dedent and indent
		while(i < lineSize){
			// Ignoring the white space between tokens
			if(i < lineSize && std::isspace(line.at(i))){
				i++;
			}

			// Start with alpha => <TOKEN_KEYWORD> or <TOKEN_IDENTIFIER>
			if(i < lineSize && std::isalpha(line.at(i))){
				std::string tempStr;
				tempStr += line.at(i);
				i++;
				while(i < lineSize && (std::isalnum(line.at(i)) || (line.at(i) == '_'))) {
					tempStr += line.at(i);
					i++;
				}
				if(keywordTrees::checkExistance(tempStr)){
					tokens.push_back(Token(TOKEN_KEYWORD, tempStr, lineNum));
				}else{
					tokens.push_back(Token(TOKEN_IDENTIFIER, tempStr, lineNum));
				}
			}

			// Start with a number => <TOKEN_NUMBER>
			if(i < lineSize && std::isdigit(line.at(i))){
				std::string tempStr;
				tempStr += line.at(i);
				i++;
				while(i < lineSize && std::isdigit(line.at(i))){
					tempStr += line.at(i);
					i++;
				}
				tokens.push_back(Token(TOKEN_NUMBER, tempStr, lineNum));
				if(i < lineSize && std::isalpha(line.at(i))) {
					EXCEPT_COD(lineNum, "No info", "An alphabetical symbol immediately after a numerical token is not allowed");
				}
			}

			// starts with a char => <TOKEN_STRING> or <TOKEN_CHAR>
			if(i < lineSize && (line.at(i) == '"')){
				std::string tempStr;
				i++;
				while(i < lineSize && line.at(i) != '"'){
					tempStr += line.at(i);
					i++;
				}
				if(i >= lineSize && line.at(i) != '"'){
					EXCEPT_COD(lineNum, "No info", "There is second quotation mark for the string");
				}
				tokens.push_back(Token(TOKEN_STRING, tempStr, lineNum));
			}

			// Finding the character literals
			if(i < lineSize && line.at(i) == '\'') {
				i++;
				#ifndef  NDEBUG
				if(i >= lineSize){
					EXCEPT_INT("Unexpected end of line after opening single quote");
				}
				#endif 
				char c = line.at(i);
				i++;
				#ifndef  NDEBUG
				if(i >= lineSize || line.at(i) != '\''){
					EXCEPT_INT("Missing closing single quote for character literal");
				}
				#endif 
				i++;
				tokens.push_back(Token(TOKEN_STRING, std::string(1, c), lineNum));
			}

			// Start with an delimiter
			if(i < lineSize){
				switch(line.at(i))
				{
				case(':'):
					{
						tokens.push_back(Token(TOKON_DOUBLECOLON, std::string(1, ':'), lineNum));
						i++;
						break;
					}
				case(';'):
					{
						tokens.push_back(Token(TOKEN_SEMICOLON, std::string(1, ';'), lineNum));
						i++;
						break;
					}
				case(','):
					{
						tokens.push_back(Token(TOKEN_COMMA, std::string(1, ','), lineNum));
						i++;
						break;
					}
				case('.'):
					{
						tokens.push_back(Token(TOKEN_DOT, std::string(1, '.'), lineNum));
						i++;
						break;
					}
				case('('):
					{
						tokens.push_back(Token(TOKEN_OPENPARAN, std::string(1, '('), lineNum));
						i++;
						break;
					}
				case(')'):
					{
						tokens.push_back(Token(TOKEN_CLOSEPARAN, std::string(1, ')'), lineNum));
						i++;
						break;
					}
				case('{'):
					{
						tokens.push_back(Token(TOKEN_OPENBARAC, std::string(1, '{'), lineNum));
						i++;
						break;
					}
				case('}'):
					{
						tokens.push_back(Token(TOKEN_CLOSEBARAC, std::string(1, '}'), lineNum));
						i++;
						break;
					}
				case('<'):
					{
						i++;
						if(i < lineSize && line.at(i) == '<'){
							tokens.push_back(Token(TOKEN_LOWEREQUAL, std::string(1, '='), lineNum));
							i++;

						}else{
							tokens.push_back(Token(TOKEN_LOWER, std::string(1, '<'), lineNum));
						}
						break;
					}
				case('>'):
					{
						i++;
						if(i < lineSize && line.at(i) == '>'){
							tokens.push_back(Token(TOKEN_BIGGEREQUAL, std::string(1, '='), lineNum));
							i++;
						}else{
							tokens.push_back(Token(TOKEN_BIGGER, std::string(1, '>'), lineNum));
						}
						break;
					}
				case('='):
					{
						i++;
						if(i < lineSize && line.at(i) == '='){
							tokens.push_back(Token (TOKEN_CHECKEQUAL, "==", lineNum));
							i++;
						}else{
							tokens.push_back(Token(TOKEN_EQUAL, std::string(1, '='), lineNum));
						}
						break;
					}
				case('%'):
					{
						tokens.push_back(Token(TOKEN_MODULE, std::string(1, '%'), lineNum));
						i++;
						break;
					}
				case('+'):
					{
						tokens.push_back(Token(TOKEN_PLUS, std::string(1, '+'), lineNum));
						i++;
						break;
					}
				case('-'):
					{
						tokens.push_back(Token(TOKEN_MINUS, std::string(1, '-'), lineNum));
						i++;
						break;
					}
				case('*'):
					{
						i++;
						if(i < lineSize && line.at(i) == '*'){

							tokens.push_back(Token(TOKEN_EXPONENTIAL, "**", lineNum));
							i++;
						}else{
							
							tokens.push_back(Token(TOKEN_MULTIPLICATION, std::string(1, '*'), lineNum));
						}
						break;
					}
				case('/'):
					{
						i++;
						if(i < lineSize && line.at(i) == '/'){
							tokens.push_back(Token(TOKEN_FLOORDIVISION, "//", lineNum));
							i++;
						}else{
							tokens.push_back(Token(TOKEN_DEVISION, std::string(1, '/'), lineNum));
						}
						break;
					}
				case('!'):
					{
						i++;
						if(line.at(i) == '='){
							tokens.push_back(Token(TOKEN_NCHECKEQUAL, "!=", lineNum));
							i++;
						}else{
							tokens.push_back(Token(TOKEN_NOT, std::string(1, '!'), lineNum));
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
						EXCEPT_COD(lineNum, "No Info" , "The python code contains a symbol that is not defined in the grammer");
						i++;
						break;
					}
				}
			}
			// Ending the line
		}
		tokens.push_back(Token(TOKEN_NEWLINE, "NewLine", lineNum));
	}

	// Generating tokens before the end of file ==> <TOKEN_DEDENT>
	while(S.size() > 1) { // We assume base indentation is 0 at bottom of stack
		S.pop();
		tokens.push_back(Token(TOKEN_DEDENT, "Dedent", lineNum));
	}
	
	// End of the file ==> <TOKEN_EOF>
	tokens.push_back(Token(TOKEN_EOF, "EndOfFileMarker", lineNum));
}


////////////////////////////////////////////////////////
/// GETTERS
std::vector<Token> MyLexor::GetTokens() noexcept
{
	return tokens;
}

std::vector<Token>& MyLexor::GetTokensRef() noexcept{
	return tokens;
}


////////////////////////////////////////////////////////
/// TEST STUFFS
void MyLexor::TestTokens()
{
	// Defining a basic function for seeing the result of the lexor
	std::cout
		<< std::endl
		<< "___________________________________" << std::endl
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