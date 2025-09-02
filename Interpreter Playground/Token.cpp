// Token.cpp
#include "Token.h"


///////////////////////////////////////////////////////////////////
/// CONCRETE TOKEN
Token::Token(std::string xTokenString)
	:
	tokenString(xTokenString),
	tokenID(0)
{
}
int Token::getTokenID()const
{
	return tokenID;
}
std::string Token::getTokenString()const
{
	return tokenString;
}


///////////////////////////////////////////////////////////////////
///Null TOKENS
unknownTok::unknownTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_NULL;
}


///////////////////////////////////////////////////////////////////
/// STRUCTURAL TOKENS
newLineTok::newLineTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_NEWLINE;
}
indentTok::indentTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_INDENT;
}
dedentTok::dedentTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_DEDENT;
}
endOfFileTok::endOfFileTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_EOF;
}


//////////////////////////////////////////////////////////////////
///	ALPHABETICAL TOKENS
identifierTok::identifierTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_IDENTIFIER;
}
keywordTok::keywordTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	int tempTokenID = keywordTrees::getKeywordAdvancedID(xTokenString);
	tokenID = tempTokenID;
}


//////////////////////////////////////////////////////////////////
/// NUMERICAL TOKENS
numericalTok::numericalTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_NUMBER;
}


//////////////////////////////////////////////////////////////////
/// OPERATOR TOKENS
operatorTok::operatorTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	// Assigning the tokenID based on the tokenString
	switch(xTokenString.at(0))
	{
	case('+'):
		{
			tokenID = TOKEN_PLUS;
			break;
		}
	case('-'):
		{
			tokenID = TOKEN_MINUS;
			break;
		}
	case('/'):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '/'){

				tokenID = TOKEN_FLOORDIVISION;

			}
			else{
				tokenID = TOKEN_DEVISION;
			}
			break;
		}
	case('*'):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '*'){
				tokenID = TOKEN_EXPONENTIAL;
			}
			else{
				tokenID = TOKEN_MULTIPLICATION;
			}
			break;
		}
	case('%'):
		{
			tokenID = TOKEN_MODULE;
			break;
		}
	case('!'):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '='){
				tokenID = TOKEN_NCHECKEQUAL;
			}
			else{
				tokenID = TOKEN_NOT;
			}
			break;
		}
	case('='):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '='){
				tokenID = TOKEN_CHECKEQUAL;
			}
			else{
				tokenID = tokenID = TOKEN_EQUAL;;
			}
			break;
		}
	case('<'):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '='){
				tokenID = TOKEN_LOWEREQUAL;
			}
			else{
				tokenID = TOKEN_LOWER;
			}
			break;
		}
	case('>'):
		{
			if(xTokenString.length() >= 2 && xTokenString.at(1) == '='){
				tokenID = TOKEN_BIGGEREQUAL;
			}
			else{
				tokenID = TOKEN_BIGGER;
			}
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////
/// DELIMITER TOKENS
delimiterTok::delimiterTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	// Checking the size of delimiter
	if(xTokenString.size() > 1){EXCEPT_INT("Something");}

	// Assigning the delimiter ID based on their string
	switch(xTokenString.at(0))
	{
	case('('):
		{
			tokenID = TOKEN_OPENPARAN;
			break;
		}
	case(')'):
		{
			tokenID = TOKEN_CLOSEPARAN;
			break;
		}
	case('['):
		{
			tokenID = TOKEN_OPENBARAC;
			break;
		}
	case(']'):
		{
			tokenID = TOKEN_CLOSEBARAC;
			break;
		}
	case('{'):
		{
			tokenID = TOKEN_OPENCURBARAC;
			break;
		}
	case('}'):
		{
			tokenID = TOKEN_CLOSECURBARAC;
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////
/// PUNCTUATION TOKEN
punctuationTok::punctuationTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	// Assigning the tokenID based on the tokenString
	if(xTokenString == std::string(1, ';')){
		tokenID = TOKEN_SEMICOLON;
	}
	else if(xTokenString == std::string(1, ':')){
		tokenID = TOKON_DOUBLECOLON;
	}
	else if(xTokenString == std::string(1, ',')){
		tokenID = TOKEN_COMMA;
	}
	else if(xTokenString == std::string(1, '.')){
		tokenID = TOKEN_DOT;
	}
}


/////////////////////////////////////////////////////////////////
/// STRING TOKENS
stringTok::stringTok(std::string xTokenString)
	:
	Token(xTokenString)
{
	tokenID = TOKEN_STRING;
}
charTok::charTok(std::string xTokenstring)
	:
	Token(xTokenstring)
{
	tokenID = TOKEN_CHAR;
}


/////////////////////////////////////////////////////////////////
/// KEYWORD STRUCTURES
std::map<std::string, int> keywordTrees::keywordMap;
keywordTrees initObj;
keywordTrees::keywordTrees()
{
	staticInitializer();
}
void keywordTrees::staticInitializer()
{
	// Creating a keyword tree for converting the tokenString to the tokenID
		keywordMap.insert(std::make_pair("if", TOKEN_IF));
		keywordMap.insert(std::make_pair("elif", TOKEN_ELIF));
		keywordMap.insert(std::make_pair("else", TOKEN_ELSE));
		keywordMap.insert(std::make_pair("while", TOKEN_WHILE));
		keywordMap.insert(std::make_pair("break", TOKEN_BREAK));
		keywordMap.insert(std::make_pair("continue", TOKEN_CONTINUE));
		keywordMap.insert(std::make_pair("True", TOKEN_TRUE));
		keywordMap.insert(std::make_pair("False", TOKEN_FALSE));
		keywordMap.insert(std::make_pair("and", TOKEN_AND));
		keywordMap.insert(std::make_pair("or", TOKEN_OR));
		keywordMap.insert(std::make_pair("not", TOKEN_NOT));
		keywordMap.insert(std::make_pair("print", TOKEN_PRINT));
		keywordMap.insert(std::make_pair("list", TOKEN_LIST));
		keywordMap.insert(std::make_pair("append", TOKEN_APPE));
}
int keywordTrees::getKeywordAdvancedID(std::string xKeywordtokenString)
{
	auto i = keywordMap.find(xKeywordtokenString);
	std::pair<std::string, int> keyPair = *i;
	return keyPair.second;
}
bool keywordTrees::checkExistance(std::string xKeywordtokenString)
{
	return keywordMap.contains(xKeywordtokenString);
}

