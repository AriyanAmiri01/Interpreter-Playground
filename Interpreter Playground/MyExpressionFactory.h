// ExpressinFactory.h
#pragma once
#include "MyExpression.h"
#include "MyException.h"
#include "Token.h"


class ExpressionFactory
{
public:
	ExpressionFactory(std::vector<Token> xTokens, int& tokensIndicator);
public:
	std::unique_ptr<expr> parse();
public:
	std::unique_ptr<expr> findExpress();
	std::unique_ptr<expr> findJoin();
	std::unique_ptr<expr> findEquality();
	std::unique_ptr<expr> findRelation();
	std::unique_ptr<expr> findNumexpr();
	std::unique_ptr<expr> findTerm();
	std::unique_ptr<expr> findUnary();
	std::unique_ptr<expr> findFactor();
public:
	bool check(int xTokenType);
	void advanceIndicator();
	void deAdvanceIndicator();
	Token previous();
	Token getToken();
	Token peek();
public:
	int& tokenIndicator;
	std::vector<Token> tokens;
};