// MyParser.h
#pragma once
#include "MyStatementFactory.h"
#include "MyExpression.h"
#include "MyException.h"
#include "Token.h"
#include <iostream>
#include <vector>


class MyParser
{
public:
	MyParser(int xTokenIndicator, std::vector<Token> xTokens);
public:
	void ASTCreator();
	void testAST();
public:
	std::vector<std::unique_ptr<stmt>> AST;
	int tokenIndicator;
	MyStatementFactory sf;
	std::vector<Token> tokens;
};