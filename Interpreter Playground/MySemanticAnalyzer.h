// MySemanticAnalyzer.h
#pragma once
#include "MyStatement.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <map>


class MySemanticAnalyzer
{
public:
	MySemanticAnalyzer(std::vector<std::unique_ptr<stmt>>&& xAST);
public:
	void interpret();
public:
	void execute(stmt& s);
	void execute(block_stmt& s);
	void execute(simple_stmt& s);
	void execute(assignment_stmt& s);
	void execute(list_stmt& s);
	void execute(append_stmt& s);
	void execute(break_stmt& s);
	void execute(continue_stmt& s);
	void execute(print_stmt& s);
	void execute(compound_stmt& s);
	void execute(if_stmt& s);
	void execute(else_stmt& s);
	void execute(while_stmt& s);
	valueExpression execute(expr& e);;
	valueExpression	execute(valueExpression& c);
	valueExpression	execute(locExpression& c);
	valueExpression	execute(orExpression& c);
	valueExpression	execute(andExpression& c);
	valueExpression	execute(numExpression& c);
	valueExpression	execute(termExpression& c);
	valueExpression	execute(equalityExpression& c);
	valueExpression	execute(relExpression& c);
	valueExpression	execute(unaryExpression& c);
	valueExpression	execute(factorExpression& c);
	valueExpression	execute(nullExpr& c);
private:
	std::vector<std::unique_ptr<stmt>> AST;
	std::map<identifier, valueExpression> symbolTable;
	std::map <identifier, std::vector <valueExpression>> listSymbolTable;
	int currentScopeNum = 0;
	int loopDepth = 0;
};