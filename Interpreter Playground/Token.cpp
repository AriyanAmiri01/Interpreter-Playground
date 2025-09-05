// Token.cpp
#include "Token.h"
#include <iostream>

///////////////////////////////////////////////////////////////////
/// CONCRETE TOKEN
Token::Token(TOKENID xTokenID, std::string xTokenString,int xLine)
	:
	tokenID(xTokenID),
	tokenString(xTokenString)
{
	// Checking if it is a token and if yes we get the exact tokenID instead of the general TOKEN_KEYWORD
	if(tokenID == TOKEN_KEYWORD){
		if(!keywordTrees::checkExistance(tokenString))
		{
			std::string errorString = "The corrisponding token does not exist in the language";
			errorString.append(tokenString);
			std::cout << tokenString;
			EXCEPT_COD(xLine, "No info about the file", errorString);
		}
		tokenID = keywordTrees::getKeywordAdvancedID(xTokenString);
	}
}
TOKENID Token::getTokenID()const
{
	return tokenID;
}
std::string Token::getTokenString()const
{
	return tokenString;
}



/////////////////////////////////////////////////////////////////
/// KEYWORD STRUCTURES
std::map<std::string, TOKENID> keywordTrees::keywordMap;
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
TOKENID keywordTrees::getKeywordAdvancedID(std::string xTokenKeywordenString)
{
	auto i = keywordMap.find(xTokenKeywordenString);
	std::pair<std::string, TOKENID> keyPair = *i;
	return keyPair.second;
}
bool keywordTrees::checkExistance(std::string xTokenKeywordenString)
{
	return keywordMap.contains(xTokenKeywordenString);
}

