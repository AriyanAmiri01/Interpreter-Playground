// MyStatement.cpp
#pragma once
#include "MyStatement.h"
#include "MySemanticAnalyzer.h"


///////////////////////////////////////////////////////////////////////
/// STATEMENT CONSTSTRUCTOR STUFFS
stmt::stmt(int xType)
	:
	stmtType(xType)
{
}

block_stmt::block_stmt(int xType)
	:
	stmt(xType)
{
}

simple_stmt::simple_stmt(int xType)
	:
	stmt(xType)
{
}

assignment_stmt::assignment_stmt(int xType, std::unique_ptr<locExpression> xLocation, std::unique_ptr<expr> xAssignValue)
	:
	simple_stmt(xType),
	location(std::move(xLocation)),
	assignValue(std::move(xAssignValue))
{
}

list_stmt::list_stmt(int xType, std::unique_ptr<locExpression> xLocation)
	:
	simple_stmt(xType),
	location(std::move(xLocation))
{
}

append_stmt::append_stmt(int xType, std::unique_ptr<locExpression> xLoc, std::unique_ptr<expr> xExpression)
	:
	simple_stmt(xType),
	location(std::move(xLoc)),
	expression(std::move(xExpression))
{
}

print_stmt::print_stmt(int xType, std::unique_ptr<expr> xExpr)
	:
	simple_stmt(STA_PRI),
	expression(std::move(xExpr))
{
}

break_stmt::break_stmt(int xType)
	:
	simple_stmt(STA_BRE)
{
}

continue_stmt::continue_stmt(int xType)
	:
	simple_stmt(xType)
{
}

compound_stmt::compound_stmt(int xType)
	:
	stmt(xType)
{
}

if_stmt::if_stmt(int xType, std::unique_ptr<expr> xCon, std::unique_ptr<block_stmt> xthen, std::unique_ptr<else_stmt> xEles)
	:
	compound_stmt(xType),
	condition(std::move(xCon)),
	thenBlock(std::move(xthen)),
	elseBlock(std::move(xEles))
{
}

else_stmt::else_stmt(int xType, std::unique_ptr<block_stmt> xThen)
	:
	compound_stmt(xType),
	thenBlock(std::move(xThen))
{
}

while_stmt::while_stmt(int xType, std::unique_ptr<expr> xCondition, std::unique_ptr<block_stmt> xThenDo)
	:
	compound_stmt(xType),
	condition(std::move(xCondition))
{
	for(auto& e : xThenDo->statements){
		thenBlock.push_back(std::move(e));
	}
}



///////////////////////////////////////////////////////////////////////
/// SPECIAL MEMBER FUNCTION
std::unique_ptr<stmts> stmts::addStatement(std::unique_ptr<stmt> xStatement)
{
	// The node is empty
	if(!statement){
		statement = std::move(xStatement);
		return std::make_unique<stmts>();
	}
	// The node is not empty
	else{
		return nextStatements->addStatement(std::move(xStatement));
	}
}
void block_stmt::addStmt(std::unique_ptr<stmt> xStmt)
{
	if(xStmt == nullptr){ EXCEPT_INT("You can not add a null statemnt to block_stmt"); }

	statements.push_back(std::move(xStmt));
}
void simple_stmt::testStmt()
{
	EXCEPT_INT("Abstract Class is not allowed to give a statement testValue");
}
void assignment_stmt::testStmt()
{
	exprVisitor argVis;
	std::cout << "<assignment_stmt>";
	location->accept(argVis);
	std::cout << ",";
	assignValue->accept(argVis);
	std::cout << "</assignment_stmt>";
}
void list_stmt::testStmt()
{
	exprVisitor argVis;
	std::cout << "<list_stmt>";
	location->accept(argVis);
	std::cout << "</list_stmt>";
}
void append_stmt::testStmt()
{
	exprVisitor argVis;
	std::cout << "<append_stmt>";
	location->accept(argVis);
	std::cout << ",";
	expression->accept(argVis);
	std::cout << "</append_stmt>";
}
void break_stmt::testStmt()
{
	std::cout <<"<Break>";
}
void continue_stmt::testStmt()
{
	std::cout << "<Break>";
}
void compound_stmt::testStmt()
{
	EXCEPT_INT("Abstract Class is not allowed to give a statement testValue");
}
void if_stmt::testStmt()
{
	exprVisitor visArg;
	std::cout << "<if:";
	std::cout << "(";
	condition->accept(visArg);
	std::cout << "),";
	std::cout << ">";
	thenBlock->testStmt();
	std::cout << "</if>";
	std::cout <<"<else>";
	elseBlock->testStmt();
	std::cout << "</else>";
}
void else_stmt::testStmt()
{
	thenBlock->testStmt();
}
void block_stmt::testStmt()
{
	for(auto const& i : statements){
		i->testStmt();
	}
}
void print_stmt::testStmt()
{
	exprVisitor argVis;
	std::cout << "<print>";
	expression->accept(argVis);
	std::cout << "</print>";
}
void while_stmt::testStmt()
{
	exprVisitor visArg;
	std::cout << "<while:";
	std::cout << "(";
	condition->accept(visArg);
	std::cout << ")>:";
	for(auto const& i : thenBlock){
		i->testStmt();
	}
	std::cout << "</while>";
}

///////////////////////////////////////////////////////////////////////
///	EXECUTE ACCEPT VISITOR FUNCTIONS
void simple_stmt::accept(MySemanticAnalyzer& v)
{
	EXCEPT_INT("soemthing");
}
void assignment_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void list_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void append_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void break_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void continue_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void print_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void if_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void compound_stmt::accept(MySemanticAnalyzer& v)
{
	EXCEPT_INT("something");
}
void else_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void while_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}
void block_stmt::accept(MySemanticAnalyzer& v)
{
	v.execute(*this);
}