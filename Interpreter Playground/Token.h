// Token.h
#pragma once
#include "MyException.h"
#include "MyEnumeration.h"
#include <string>
#include <vector>
#include <memory>
#include <map>



///////////////////////////////////////////////////////////////////
/// CONCRETE TOKEN
class Token
{
public:
	Token(TOKENID xTokenID = TOKEN_NULL, std::string xTokenString = "without string", int xLine = 0);
public:
	TOKENID getTokenID() const;
	std::string getTokenString() const;
protected:
	TOKENID tokenID;
	std::string tokenString;
};



/////////////////////////////////////////////////////////////////
/// KEYWORD STRUCTURES
class keywordTrees
{
public:
	keywordTrees();
public:
	static void staticInitializer();
	static TOKENID getKeywordAdvancedID(std::string xTokenKeywordenString);
	static bool checkExistance(std::string xTokenKeywordenString);
private:
	static std::map <std::string, TOKENID> keywordMap;
};