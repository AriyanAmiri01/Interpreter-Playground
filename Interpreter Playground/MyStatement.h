// MyStatement.h
#pragma once
#include "MyExpression.h"
#include "Token.h"
#include <string>
#include <vector>
#include <memory>
#include <map>



///////////////////////////////////////////////////////////////////////
/// VISITOR STUFFS
class MySemanticAnalyzer;

///////////////////////////////////////////////////////////////////////
/// STATEMENT BASECLASS
class stmt
{
public:
	stmt(int xType);
	virtual void testStmt() = 0;
	virtual void accept(MySemanticAnalyzer& v) = 0;
public:
	int stmtType = 0;
};
class stmts
{
public:
	stmts() = default;
public:
	std::unique_ptr<stmts> addStatement(std::unique_ptr<stmt> xStatement);
private:
	std::unique_ptr<stmt> statement;
	std::unique_ptr<stmts> nextStatements;
};

///////////////////////////////////////////////////////////////////////
/// STATEMENT DECLARATION STUFS
class block_stmt : stmt
{
	using stmt::stmt;
public:
	block_stmt(int xType);
public:
	void addStmt(std::unique_ptr<stmt> xStmt);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::vector<std::unique_ptr<stmt>> statements;
};

class simple_stmt :public stmt
{
	using stmt::stmt;
public:
	simple_stmt(int xType);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
};

class assignment_stmt :public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	assignment_stmt(int xType, std::unique_ptr<locExpression> xLocation, std::unique_ptr<expr> xAssignValue);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<locExpression> location;
	std::unique_ptr<expr> assignValue;
};

class list_stmt :public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	list_stmt(int xType, std::unique_ptr<locExpression> xLocation);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<locExpression> location;
	std::vector<std::unique_ptr<expr>> elements;
};

class append_stmt :public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	append_stmt(int xType, std::unique_ptr<locExpression> xLoc, std::unique_ptr<expr> xExpression);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<locExpression> location;
	std::unique_ptr<expr> expression;
};

class break_stmt :public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	break_stmt(int xType);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
};

class continue_stmt :public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	continue_stmt(int xType);
	void testStmt() override;
	virtual void accept(MySemanticAnalyzer& v) override;
};


class compound_stmt : public stmt
{
	using stmt::stmt;
public:
	compound_stmt(int xType);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
};

class else_stmt :public compound_stmt
{
	using compound_stmt::compound_stmt;
public:
	else_stmt(int xType, std::unique_ptr<block_stmt> xThen);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<block_stmt> thenBlock;
};

class if_stmt : public compound_stmt
{
	using compound_stmt::compound_stmt;
public:
	if_stmt(int xType, std::unique_ptr<expr> xCon, std::unique_ptr<block_stmt> xthen, std::unique_ptr<else_stmt> xEles);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<expr> condition;
	std::unique_ptr<block_stmt> thenBlock;
	std::unique_ptr<else_stmt> elseBlock;
};


class print_stmt : public simple_stmt
{
	using simple_stmt::simple_stmt;
public:
	print_stmt(int xType, std::unique_ptr<expr> xExpr);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<expr> expression;
};
class while_stmt :public compound_stmt
{
	using compound_stmt::compound_stmt;
public:
	while_stmt(int xType, std::unique_ptr<expr> xCondition, std::unique_ptr<block_stmt> xThenBlock);
	void testStmt() override;
	void accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<expr> condition;
	std::vector<std::unique_ptr<stmt>> thenBlock; // I did not use block_stmt because there are differences between break and continue and other stmt
};



