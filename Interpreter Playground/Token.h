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
	Token(std::string xTokenString);
public:
	int getTokenID() const;
	std::string getTokenString() const;
protected:
	int tokenID;
	std::string tokenString;
};


///////////////////////////////////////////////////////////////////
/// GENERAL TOKENS
class unknownTok :public Token
{
	using Token::Token;
public:
	unknownTok(std::string xTokenString);
};


///////////////////////////////////////////////////////////////////
/// STRUCTURAL TOKENS
class newLineTok :public Token
{
	using Token::Token;
public:
	newLineTok(std::string xTokenString);
};
class dedentTok :public Token
{
	using Token::Token;
public:
	dedentTok(std::string xTokenString);
};
class indentTok :public Token
{
	using Token::Token;
public:
	indentTok(std::string xTokenString);
};
class endOfFileTok :public Token
{
	using Token::Token;
public:
	endOfFileTok(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
///	ALPHABETICAL TOKENS
class identifierTok :public Token
{
	using Token::Token;
public:
	identifierTok(std::string xTokenString);
};
class keywordTok :public Token
{
	using Token::Token;
public:
	keywordTok(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
/// NUMERICAL TOKENS
class numericalTok :public Token
{
	using Token::Token;
public:
	numericalTok(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
/// OPERATOR TOKENS
class operatorTok :public Token
{
	using Token::Token;
public:
	operatorTok(std::string xTokenString);
};


/////////////////////////////////////////////////////////////////
/// DELIMITER TOKENS
class delimiterTok :public Token
{
	using Token::Token;
public:
	delimiterTok(std::string xTokenString);
};


/////////////////////////////////////////////////////////////////
/// PUNCTUATION TOKEN
class punctuationTok :public Token
{
	using Token::Token;
public:
	punctuationTok(std::string xTokenString);
};


/////////////////////////////////////////////////////////////////
/// STRING TOKENS
class stringTok :public Token
{
	using Token::Token;
public:
	stringTok(std::string xTokenString);
};
class charTok :public Token
{
	using Token::Token;
public:
	charTok(std::string xTokenString);
};

/////////////////////////////////////////////////////////////////
/// KEYWORD STRUCTURES
class keywordTrees
{
public:
	keywordTrees();
public:
	static void staticInitializer();
	static int getKeywordAdvancedID(std::string xKeywordtokenString);
	static bool checkExistance(std::string xKeywordtokenString);
private:
	static std::map <std::string, int> keywordMap;
};