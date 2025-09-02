// ExpressionFactory.cpp
#include "MyExpressionFactory.h"


///////////////////////////////////////////////////////
/// EXPRESSION FACTORY STUFFS
ExpressionFactory::ExpressionFactory(std::vector<Token> xTokens, int& xTokensIndicator)
	:
	tokens(xTokens),
	tokenIndicator(xTokensIndicator)
{
	if(tokens.empty()){ EXCEPT_INT("The tokens vector is empty"); }
	if(tokenIndicator >= tokens.size()){ EXCEPT_INT("Tokens indicator has passed its upper boundary"); }
	if(tokenIndicator < 0){ EXCEPT_INT("Token indicator was negative"); }
}


/////////////////////////////////////////////////////////////
// ACTUAL FIND EXPRESSION
std::unique_ptr<expr> ExpressionFactory::parse()
{
	return findExpress();
}
std::unique_ptr<expr> ExpressionFactory::findExpress()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findJoin();
	while(check(TOKEN_OR)){
		// Getting the right handside of the composite Expression
		std::unique_ptr<expr> right = findJoin();

		// Converting the whole composite expression as a single left simple expression
		left = std::make_unique<orExpression>(TOKEN_OR, std::move(left), std::move(right));
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findJoin()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findEquality();

	while(check(TOKEN_AND)){
		// Getting the right handside of the composite Expression
		std::unique_ptr<expr> right = findEquality();

		// Converting the whole composite expression as a single left simple expression
		left = std::make_unique<andExpression>(TOKEN_AND, std::move(left), std::move(right));
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findEquality()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findRelation();

	while(true){
		if(check(TOKEN_CHECKEQUAL))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findRelation();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<equalityExpression>(EXP_EQU, std::move(left), std::move(right));
		}
		else if(check(TOKEN_NCHECKEQUAL)){
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findRelation();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<equalityExpression>(EXP_NEQ, std::move(left), std::move(right));
		}
		else
		{
			break;
		}
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findRelation()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findNumexpr();

	while(true)
	{
		if(check(TOKEN_BIGGER))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findNumexpr();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<relExpression>(EXP_GRE, std::move(left), std::move(right));
		}
		else if(check(TOKEN_BIGGEREQUAL))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findNumexpr();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<relExpression>(EXP_GEQ, std::move(left), std::move(right));
		}
		else if(check(TOKEN_LOWER))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findNumexpr();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<relExpression>(EXP_LES, std::move(left), std::move(right));
		}
		else if(check(TOKEN_LOWEREQUAL)) {
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findNumexpr();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<relExpression>(EXP_LEE, std::move(left), std::move(right));
		}
		else {
			break;
		}
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findNumexpr()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findTerm();

	while(true)
	{
		if(check(TOKEN_PLUS))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findTerm();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<numExpression>(EXP_PLU, std::move(left), std::move(right));
		}
		else if(check(TOKEN_MINUS))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findTerm();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<numExpression>(EXP_MIN, std::move(left), std::move(right));
		}
		else {
			break;
		}
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findTerm()
{
	// Getting the left handside of the composite Expression
	std::unique_ptr<expr> left = findUnary();

	while(true)
	{
		if(check(TOKEN_MULTIPLICATION))
		{
			// Getting the right handside of the composite Expression
			std::unique_ptr<expr> right = findUnary();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<termExpression>(EXP_MUL, std::move(left), std::move(right));

		}
		else if(check(TOKEN_DEVISION))
		{
			// Getting the right handside of the composite Expressions
			std::unique_ptr<expr> right = findUnary();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<termExpression>(EXP_DIV, std::move(left), std::move(right));
		}
		else if(check(TOKEN_MODULE))
		{
			// Getting the right handside of the composite Expressions
			std::unique_ptr<expr> right = findUnary();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<termExpression>(EXP_MOD, std::move(left), std::move(right));
		}
		else if(check(TOKEN_EXPONENTIAL))
		{
			// Getting the right handside of the composite Expressions
			std::unique_ptr<expr> right = findUnary();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<termExpression>(EXP_EPN, std::move(left), std::move(right));
		}
		else if(check(TOKEN_FLOORDIVISION))
		{
			// Getting the right handside of the composite Expressions
			std::unique_ptr<expr> right = findUnary();

			// Converting the whole composite expression as a single left simple expression
			left = std::make_unique<termExpression>(EXP_FLD, std::move(left), std::move(right));
		}
		else
		{
			break;
		}
	}
	return left;
}
std::unique_ptr<expr> ExpressionFactory::findUnary()
{
	// Creating the composite expression of a unary and a factor
	if(check(TOKEN_NOT)) {
		// Returning the whole setup as a new simple expression and calling recursively
		return std::make_unique<unaryExpression>(EXP_NOT, findUnary());
	}
	else if(check(TOKEN_MINUS)) {
		// Returning the whole setup as a new simple expression and calling recursively
		return std::make_unique<unaryExpression>(EXP_NEG, findUnary());
	}
	return findFactor();
}
std::unique_ptr<expr> ExpressionFactory::findFactor()
{
	// In the case we have recursive expression
	if(check(TOKEN_OPENPARAN)){
		std::unique_ptr<expr> inside = findExpress();
		if(!check(TOKEN_CLOSEPARAN)){
			EXCEPT_INT("Something");
		}
		return inside;
	}

	// Finding the simple factor expression
	if(check(TOKEN_TRUE))
	{
		// Finding the valueExpressioneral with its type for factorExpression
		std::unique_ptr<valueExpression> v = std::make_unique<valueExpression>();
		v->valType = VAL_BOO;
		v->expType = EXP_VAL;
		v->boolValue = true;
		return std::move(v);
	}
	else if(check(TOKEN_FALSE))
	{
		// Finding the valueExpressioneral with its type for factorExpression
		std::unique_ptr<valueExpression> v = std::make_unique<valueExpression>();
		v->valType = VAL_BOO;
		v->expType = EXP_VAL;
		v->boolValue = false;
		return std::move(v);
	}
	else if(check(TOKEN_NUMBER))
	{
		// Finding the valueExpressioneral with its type for factorExpression
		std::unique_ptr<valueExpression> v = std::make_unique<valueExpression>();
		v->valType = VAL_INT;
		v->expType = EXP_VAL;
		v->numberValue = std::stoi(previous().getTokenString());
		return std::move(v);
	}
	else if(check(TOKEN_IDENTIFIER))
	{
		// Extracting locExpression material and initializing its dummy expression
		std::unique_ptr<identifier> tempId = std::make_unique<identifier>(previous().getTokenString(), -5);
		return std::make_unique<locExpression>(std::move(tempId), nullptr);
	}
	else
	{
		EXCEPT_INT("Unknown factor has been found");
	}
}


///////////////////////////////////////////////////////
// GENERAL FUNCTIONS
bool ExpressionFactory::check(int xTokenType)
{
	// Error checking 
	if(tokenIndicator >= tokens.size()){ EXCEPT_INT("Tokens indicator has passed its upper boundary"); }
	if(tokenIndicator < 0){ EXCEPT_INT("Token indicator was negative"); }

	// Finding token and advancing the tokenIndicator
	if(tokens.at(tokenIndicator).getTokenID() == xTokenType){
		advanceIndicator();
		return true;
	}
	// Not finding the token and not advancing the token indiator
	else{
		return false;
	}
}
void ExpressionFactory::advanceIndicator()
{
	if(tokenIndicator >= tokens.size()) {
		EXCEPT_INT("Tried to advance beyond last token");
	}

	// Error checking
	if(tokenIndicator + 1 >= tokens.size()) { EXCEPT_INT("Tried to advance the tokenIndicator to a non valid boundary"); }

	// Advanicn the token indicator
	tokenIndicator++;
}
void ExpressionFactory::deAdvanceIndicator()
{
	// Error checking
	if(tokenIndicator < 1){ EXCEPT_INT("Tried to deadvance the tokenInicator lower than 0"); }

	// deAdvancing the token indicator
	tokenIndicator--;
}
Token ExpressionFactory::previous()
{
	// Error checking
	if(tokenIndicator == 0) { EXCEPT_INT("Called previous() at beginning of token stream"); }

	// Getting the previous token
	return tokens.at(tokenIndicator - 1);
}
Token ExpressionFactory::getToken()
{
	// Error Checking
	if(tokenIndicator >= tokens.size()){ EXCEPT_INT("Tried to get a token at a non valid boundary"); }
	if(tokenIndicator < 0){ EXCEPT_INT("Tried to deadvance the tokenInicator lower than 0"); }

	// Advancing and getting the token
	int tempIndicator = tokenIndicator;
	advanceIndicator();
	return tokens.at(tempIndicator);
}
Token ExpressionFactory::peek()
{
	// Error checking 
	if(tokenIndicator >= tokens.size()){ EXCEPT_INT("Tried to peek a token at a passed boundary"); }
	if(tokenIndicator < 0){ EXCEPT_INT("Tried to peek a token at a less than 0 boundary"); }

	// Getting the token without advancing the tokenIndicator
	return tokens.at(tokenIndicator);
}