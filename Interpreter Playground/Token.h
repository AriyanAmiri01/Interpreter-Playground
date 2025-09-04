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
	TOKENID getTokenID() const;
	std::string getTokenString() const;
protected:
	TOKENID tokenID;
	std::string tokenString;
};


///////////////////////////////////////////////////////////////////
/// GENERAL TOKENS
class TokenUnknown :public Token
{
	using Token::Token;
public:
	TokenUnknown(std::string xTokenString);
};


///////////////////////////////////////////////////////////////////
/// STRUCTURAL TOKENS
class TokenNewline :public Token
{
	using Token::Token;
public:
	TokenNewline(std::string xTokenString);
};
class TokenDedent :public Token
{
	using Token::Token;
public:
	TokenDedent(std::string xTokenString);
};
class TokenIndent :public Token
{
	using Token::Token;
public:
	TokenIndent(std::string xTokenString);
};
class TokenEOF :public Token
{
	using Token::Token;
public:
	TokenEOF(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
///	ALPHABETICAL TOKENS
class TokenIdentifier :public Token
{
	using Token::Token;
public:
	TokenIdentifier(std::string xTokenString);
};
class TokenKeyword :public Token
{
	using Token::Token;
public:
	TokenKeyword(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
/// NUMERICAL TOKENS
class TokenNumerical :public Token
{
	using Token::Token;
public:
	TokenNumerical(std::string xTokenString);
};


//////////////////////////////////////////////////////////////////
/// OPERATOR TOKENS
class TokenOperator :public Token
{
	using Token::Token;
public:
	TokenOperator(std::string xTokenString);
};


/////////////////////////////////////////////////////////////////
/// DELIMITER TOKENS
class TokenDelimiter :public Token
{
	using Token::Token;
public:
	TokenDelimiter(std::string xTokenString);
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
	static int getKeywordAdvancedID(std::string xTokenKeywordenString);
	static bool checkExistance(std::string xTokenKeywordenString);
private:
	static std::map <std::string, int> keywordMap;
};