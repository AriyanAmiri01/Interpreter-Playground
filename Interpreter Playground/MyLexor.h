#pragma once
// MyLexor.h
#include "MyException.h" 
#include "Token.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <stack>


class  MyLexor
{
public:
	MyLexor(std::string xFile);
public:
	void Tokenize();
	std::vector<Token> GetTokens() noexcept;
	std::vector<Token>& GetTokensRef() noexcept;
	void TestTokens();
private:
	std::vector<Token> tokens;
	std::stringstream oss;
};