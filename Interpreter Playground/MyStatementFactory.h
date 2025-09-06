// MyStatementFactory.h
#pragma once
#include "MyExpressionFactory.h"
#include "MyExpression.h"
#include "MyStatement.h"
#include "Token.h"


class MyStatementFactory
{
public:
	MyStatementFactory(std::vector<Token>& xTokens);
	std::unique_ptr<stmt> FindStatement();
public:
	std::unique_ptr<block_stmt> ParseBlock_stmt();
	std::unique_ptr<assignment_stmt> ParseAssign_stmt(std::string xVarName);
	std::unique_ptr<list_stmt> ParseList_stmt(std::string xVarName);
	std::unique_ptr<append_stmt> ParseAppend_stmt(std::string xVarName);
	std::unique_ptr<continue_stmt> ParseContinue_stmt();
	std::unique_ptr<break_stmt> ParseBreak();
	std::unique_ptr<print_stmt> ParsePrint_stmt();
	std::unique_ptr<if_stmt> ParseIf_stmt();
	std::unique_ptr<else_stmt> ParseElse_stmt();
	std::unique_ptr<while_stmt> ParseWhile_stmt();
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
	std::vector<Token>& tokens;
};