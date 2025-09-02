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
	std::vector<Token> getTokens();
	void testTokens();	// Will be just for debugging
private:
	std::vector<Token> tokens;
	std::stringstream oss;
	std::string line;
	std::stack<int> S;
};