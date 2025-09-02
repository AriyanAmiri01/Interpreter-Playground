// Expression.cpp
#pragma once
#include "MyExpression.h"


///////////////////////////////////////////////////////////////////////////////
/// VALUE EXPRESSION STUFFS
bool valueExpression::getBoolValue()
{
	switch(valType)
	{
	case(VAL_BOO):
		{
			return boolValue;
		}
	case(VAL_INT):
		{
			if(numberValue == 0){
				return false;
			}
			else{
				return true;
			}
		}
	case(VAL_STR):
		{
			if(stringValue == ""){
				return false;
			}
			else{
				return true;
			}
		}
	default:
		EXCEPT_INT("The inserted value has not been defined yet");
	}
}
bool valueExpression::operator==(const valueExpression& xRight) const
{
	// Checking the valueExpression of the right handside first
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue == xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue == xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue == xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}
bool valueExpression::operator<(const valueExpression& xRight) const
{
	// Checking the valueExpression of the right handside first
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue < xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue < xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue < xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}
bool valueExpression::operator<=(const valueExpression& xRight) const
{
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue <= xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue <= xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue <= xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}
bool valueExpression::operator>=(const valueExpression& xRight) const
{
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue >= xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue >= xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue >= xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}
bool valueExpression::operator>(const valueExpression& xRight) const
{
	// Checking the valueExpression of the right handside first
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue > xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue > xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue > xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}
bool valueExpression::operator!=(const valueExpression& xRight) const
{
	// Checking the valueExpression of the right handside first
	switch(valType)
	{
	case(VAL_NDE):
		{
			EXCEPT_INT("Something");
			return 0;
		}
	case(VAL_BOO):
		{
			if(xRight.valType != VAL_BOO){ EXCEPT_INT("Something"); }
			return boolValue != xRight.boolValue;
		}
	case(VAL_INT):
		{
			if(xRight.valType != VAL_INT){ EXCEPT_INT("Something"); }
			return numberValue != xRight.numberValue;
		}
	case(VAL_STR):
		{
			if(xRight.valType != VAL_STR){ EXCEPT_INT("Something"); }
			return stringValue != xRight.stringValue;
		}
	default:
		EXCEPT_INT("Something");
		return 0;
	}
}


///////////////////////////////////////////////////////////////////////////////
/// OTHER EXPRESSIONS
expr::expr(int xType, int xValType)
	:
	expType(xType),
	valType(xValType)
{
}
valueExpression::valueExpression()
	:
	expr(EXP_VAL, valType)
{
}
locExpression::locExpression(std::unique_ptr<identifier> xId, std::unique_ptr<expr> xExpression)
	:
	expr(EXP_LOC, VAL_NDE),
	id(std::move(xId)),
	expression(std::move(xExpression))
{
	if(expression){
		valType = expression->valType;
	}
}
orExpression::orExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(EXP_OR, VAL_BOO),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
andExpression::andExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(EXP_AND, VAL_BOO),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
equalityExpression::equalityExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(xType, VAL_BOO),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
relExpression::relExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(xType, VAL_BOO),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
termExpression::termExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(xType, VAL_INT),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
numExpression::numExpression(int xType, std::unique_ptr<expr> xLeft, std::unique_ptr<expr> xRight)
	:
	expr(xType, VAL_INT),
	left(std::move(xLeft)),
	right(std::move(xRight))
{
}
unaryExpression::unaryExpression(int xType, std::unique_ptr<expr> xRight)
	:
	expr(xType, VAL_NDE),
	right(std::move(xRight))
{
	if(xType == EXP_NEG){
		valType = VAL_BOO;
	}
	else if(xType == EXP_NEG){
		valType = VAL_INT;
	}
}
factorExpression::factorExpression(int xType, std::unique_ptr<expr> xValue)
	:
	expr(xType, VAL_NDE),
	value(std::move(xValue))
{
	if(value == nullptr){ EXCEPT_INT("Tried to create a factor expression using a nullptr"); }
}
nullExpr::nullExpr(int xType)
	:
	expr(xType, VAL_NDE)
{
}


///////////////////////////////////////////////////////////////////////////////
/// CLONE EXPRESSION STUFFS
std::unique_ptr<expr> locExpression::clone() const
{
	return std::make_unique<locExpression>(
		std::unique_ptr<identifier>(id ? id->clone() : nullptr),
		expression ? expression->clone() : nullptr
	);
}
std::unique_ptr<expr> valueExpression::clone() const
{
	return std::make_unique<valueExpression>(*this);
}
std::unique_ptr<expr> orExpression::clone() const
{
	return std::make_unique<orExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> andExpression::clone() const
{
	return std::make_unique<andExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> equalityExpression::clone() const
{
	return std::make_unique<equalityExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> relExpression::clone() const
{
	return std::make_unique<relExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> numExpression::clone() const
{
	return std::make_unique<numExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> termExpression::clone() const
{
	return std::make_unique<termExpression>(
		expType,
		left ? left->clone() : nullptr,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> unaryExpression::clone() const
{
	return std::make_unique<unaryExpression>(
		expType,
		right ? right->clone() : nullptr
	);
}
std::unique_ptr<expr> factorExpression::clone() const
{
	return std::make_unique<factorExpression>(
		expType,
		value ? value->clone() : nullptr
	);
}
std::unique_ptr<expr> nullExpr::clone() const
{
	// I am not sure about this
	return std::make_unique<nullExpr>(*this);
}




///////////////////////////////////////////////////////////////////////////////
/// ACCEPT TEST PRINT VISITOR
void nullExpr::accept(exprVisitor& v)
{
	v.visit(*this);
}
void valueExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void locExpression::accept(exprVisitor& v)
{

	v.visit(*this);

}
void orExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void andExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void equalityExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void relExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void numExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void termExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void unaryExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}
void factorExpression::accept(exprVisitor& v)
{
	v.visit(*this);
}


///////////////////////////////////////////////////////////////////////////////
/// VISIT TEST PRINT VISITOR
void exprVisitor::visit(valueExpression& c)
{
	switch(c.valType)
	{
	case(VAL_NDE):
		{
			std::cout << "[" << "notDefined" << "]";
			break;
		}
	case(VAL_BOO):
		{
			std::cout << "[" << c.boolValue << "]";
			break;
		}
	case(VAL_INT):
		{
			std::cout << "[" << c.numberValue << "]";
			break;
		}
	case(VAL_STR):
		{
			std::cout << "[" << c.stringValue << "]";
			break;
		}
	default:
		EXCEPT_INT("something:");
		break;
	}
}
void exprVisitor::visit(locExpression& c)
{
	std::cout << "[locExpr]";
	std::cout << c.id->name;
	std::cout << "[locExpr]";
}
void exprVisitor::visit(orExpression& c)
{
	std::cout << "[orExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/orExpr]";
}
void exprVisitor::visit(andExpression& c)
{
	std::cout << "[andExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/andExpr]";
}
void exprVisitor::visit(equalityExpression& c)
{
	std::cout << "[equalityExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/equalityExpr]";
}
void exprVisitor::visit(relExpression& c)
{
	std::cout << "[relExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/relExpr]";
}
void exprVisitor::visit(numExpression& c)
{
	std::cout << "[NumExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/NumExpr]";
}
void exprVisitor::visit(termExpression& c)
{
	std::cout << "[termExpr]";
	c.left->accept(*this);
	std::cout << ",";
	c.right->accept(*this);
	std::cout << "[/termExpr]";
}
void exprVisitor::visit(unaryExpression& c)
{
	std::cout << "[unaryExpr]";
	c.right->accept(*this);
	std::cout << "[/unaryExpr]";
}
void exprVisitor::visit(factorExpression& c)
{
	std::cout << "[factorExpr]";
	c.value->accept(*this);
	std::cout << "[factorExpr]";
}
void exprVisitor::visit(nullExpr& c)
{
	std::cout << "[nullExpr]";
}