// MyStatementFactory.h
#pragma once
#include "MyExpressionFactory.h"
#include "MyExpression.h"
#include "MyStatement.h"
#include "Token.h"


class MyStatementFactory
{
public:
	MyStatementFactory(int xTokenIndicator, std::vector<Token> xTokens);
public:
	std::unique_ptr<stmt> findStatement();
public:
	std::unique_ptr<block_stmt> parseBlock_stmt();
	std::unique_ptr<assignment_stmt> parseAssign_stmt(std::string xVarName);
	std::unique_ptr<list_stmt> parseList_stmt(std::string xVarName);
	std::unique_ptr<append_stmt> parseAppend_stmt(std::string xVarName);
	std::unique_ptr<continue_stmt> parseContinue_stmt();
	std::unique_ptr<break_stmt> parseBreak();
	std::unique_ptr<print_stmt> parsePrint_stmt();
	std::unique_ptr<if_stmt> parseIf_stmt();
	std::unique_ptr<else_stmt> parseElse_stmt();
	std::unique_ptr<while_stmt> parseWhile_stmt();
public:
	bool check(int xTokenType);
	bool checkNoAdvance(int xTokenType);
	void advanceIndicator();
	void deAdvanceIndicator();
	Token previous();
	Token getToken();
	Token peek();
private:
	int tokenIndicator = 0;
	std::vector<Token> tokens;
};