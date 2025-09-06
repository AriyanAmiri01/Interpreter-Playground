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
	MyParser(std::vector<Token>& xTokens);
public:
	void ASTCreator();
	void TestAST();
public:
	std::vector<std::unique_ptr<stmt>> AST;
	std::vector<Token>& tokens;
};