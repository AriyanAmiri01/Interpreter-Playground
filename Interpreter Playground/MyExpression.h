// Expression.h
#pragma once
#include "MyEnumeration.h"
#include "MyIdentifier.h"
#include "MyException.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>


/////////////////////////////////////////////////////////////////
///	PRINT TEST EXPRESSION VISITOR STUFFS
class MySemanticAnalyzer;
class valueExpression;
class locExpression;
class orExpression;
class andExpression;
class equalityExpression;
class relExpression;
class numExpression;
class termExpression;
class unaryExpression;
class factorExpression;
class nullExpr;
class exprVisitor
{
public:
	virtual void visit(valueExpression& c);
	virtual void visit(locExpression& c);
	virtual void visit(orExpression& c);
	virtual void visit(andExpression& c);
	virtual void visit(equalityExpression& c);
	virtual void visit(relExpression& c);
	virtual void visit(numExpression& c);
	virtual void visit(termExpression& c);
	virtual void visit(unaryExpression& c);
	virtual void visit(factorExpression& c);
	virtual void visit(nullExpr& c);

};

///////////////////////////////////////////////////////////////////
/// EXPRESSION DECLARATIONS
class expr
{
public:
	expr(int xType, int xValType);
public:
	virtual valueExpression accept(MySemanticAnalyzer& v) = 0;
	virtual void accept(exprVisitor& v) = 0;
	virtual std::unique_ptr<expr> clone() const = 0;
public:
	int expType;
	int valType;
};
class valueExpression :public expr
{
	using expr::expr;
public:
	valueExpression();
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	void accept(exprVisitor& v)override;
	std::unique_ptr<expr> clone() const override;
public:
	bool getBoolValue();
	bool operator==(const valueExpression& xRight) const;
	bool operator<(const valueExpression& xRight) const;
	bool operator <= (const valueExpression& xRight) const;
	bool operator >= (const valueExpression& xRight) const;
	bool operator>(const valueExpression& xRight) const;
	bool operator!=(const valueExpression& xRight) const;

public:
	std::string stringValue = {};
	int numberValue = 0;
	bool boolValue = false;
};
class locExpression :public expr
{
	using expr::expr;
public:
	locExpression(std::unique_ptr<identifier> xId, std::unique_ptr<expr> xExpression);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	void accept(exprVisitor& v)override;
	std::unique_ptr<expr> clone() const override;
public:
	std::unique_ptr<identifier> id;
	std::unique_ptr<expr> expression;
};
class orExpression :public expr
{
	using expr::expr;
public:
	orExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class andExpression :public expr
{
	using expr::expr;
public:
	andExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class equalityExpression :public expr
{
	using expr::expr;
public:
	equalityExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class relExpression :public expr
{
	using expr::expr;
public:
	relExpression(int xType, std::unique_ptr<expr> xLValue, std::unique_ptr<expr> xRValue);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class numExpression :public expr
{
	using expr::expr;
public:
	numExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class termExpression : public expr
{
	using expr::expr;
public:
	termExpression(int xType, std::unique_ptr <expr> xLeft, std::unique_ptr<expr> xRight);
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> left;
	std::unique_ptr<expr> right;
};
class unaryExpression : public expr
{
	using expr::expr;
public:
	valueExpression accept(MySemanticAnalyzer& v) override;
	unaryExpression(int xType, std::unique_ptr<expr> xRight);
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
	std::unique_ptr<expr> right;
};
class factorExpression :public expr
{
	using expr::expr;
public:
	factorExpression(int xType, std::unique_ptr<expr> xValue);
	valueExpression accept(MySemanticAnalyzer& v) override;
	std::unique_ptr<expr> clone() const override;
	void accept(exprVisitor& v)override;
public:
	std::unique_ptr<expr> value;
};
class nullExpr :public expr
{
	using expr::expr;
public:
	nullExpr(int xType);
	void accept(exprVisitor& v)override;
	valueExpression accept(MySemanticAnalyzer& v) override;
public:
	std::unique_ptr<expr> clone() const override;
};