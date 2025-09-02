// MyMyStatementFactory.cpp
#include "MyStatementFactory.h"


///////////////////////////////////////////////////////////////////////
/// GENERAL STATEMENT STUFFS
MyStatementFactory::MyStatementFactory(int xTokenIndicator, std::vector<Token> xTokens)
	:
	tokenIndicator(xTokenIndicator),
	tokens(xTokens)
{
}


///////////////////////////////////////////////////////////////////////
/// PARSE FUNCTIONS STUFFS
std::unique_ptr<stmt> MyStatementFactory::findStatement()
{
	// Finding difference stmt based on the first token
	if(check(TOKEN_IDENTIFIER)){

		// Finding loaction's identifier 
		std::string varName = previous().getTokenString();

		// It is an assignment or list or append stmt or error
		if(check(TOKEN_EQUAL))
		{
			if(check(TOKEN_LIST))
			{
				return parseList_stmt(varName);
			}
			else
			{
				return parseAssign_stmt(varName);
			}
		}
		else if(check(TOKEN_DOT))
		{
			return parseAppend_stmt(varName);
		}
		EXCEPT_INT("after a identifier a dot or a = token is neccesasary");
		return nullptr;
	}
	else if(check(TOKEN_BREAK))
	{
		return parseBreak();
	}
	else if(check(TOKEN_CONTINUE))
	{
		return parseContinue_stmt();
	}
	else if(check(TOKEN_PRINT))
	{
		return parsePrint_stmt();
	}
	else if(check(TOKEN_IF))
	{
		return parseIf_stmt();
	}
	else if(check(TOKEN_WHILE))
	{
		return parseWhile_stmt();
	}
	else if(check(TOKEN_NEWLINE)){
		return findStatement();
	}
	else if(check(TOKEN_EOF)){
		return nullptr;
	}
	else if(check(TOKEN_DEDENT)){
		deAdvanceIndicator();
		return nullptr;
	}
	else
	{
		EXCEPT_INT("There is no type of statement corrisponding to this token");
		return nullptr;
	}
}
std::unique_ptr<block_stmt> MyStatementFactory::parseBlock_stmt()
{
	// The container of the block_stmt
	std::unique_ptr<block_stmt> block = std::make_unique<block_stmt>(STA_BLO);

	// Getting into the block
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("A new line after the if condition is neccessary"); }
	if(!check(TOKEN_INDENT)){ EXCEPT_INT("A INDENT after the if condition is neccessary"); }

	// Looping based on the block scope which gets closed after a dedent
	while(!check(TOKEN_DEDENT)){
		// Adding current statements to the block_stmt
		auto temp = findStatement();
		if(temp != nullptr){
			block->addStmt(std::move(temp));
		}
	}
	return block;
}
std::unique_ptr<assignment_stmt> MyStatementFactory::parseAssign_stmt(std::string xVarName)
{
	// If it is assignment_stmt
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> value = fac.parse();

	// Creating the variable LocExpression
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	if(tempId == nullptr){ EXCEPT_INT("Something"); }
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);
	if(tempLoc == nullptr){ EXCEPT_INT("Something"); }

	// Checking the endline after the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("A new line at the end of assignment_stmt is neccesary"); }

	return std::make_unique<assignment_stmt>(STA_ASS, std::move(tempLoc), std::move(value));
}
std::unique_ptr<list_stmt> MyStatementFactory::parseList_stmt(std::string xVarName)
{
	// If it is a list_stmt
	if(!check(TOKEN_OPENPARAN)){ EXCEPT_INT("Something"); }

	// For now the interpreter only allows list declaration
	if(!check(TOKEN_CLOSEPARAN)){ EXCEPT_INT("Something"); }
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("Something"); }
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);

	if(tempLoc == nullptr){ EXCEPT_INT("Something"); }
	return std::make_unique<list_stmt>(STA_ASS, std::move(tempLoc));
}
std::unique_ptr<append_stmt> MyStatementFactory::parseAppend_stmt(std::string xVarName)
{
	// Syntax stuffs
	if(!check(TOKEN_APPE)){ EXCEPT_INT("Only append function has been defined into the interpreter"); }
	if(!check(TOKEN_OPENPARAN)){ EXCEPT_INT("A parantes after a function call is neccassary"); }

	// Finding the append Expression
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> value = fac.parse();
	if(value == nullptr){ EXCEPT_INT("Something"); }
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	if(tempId == nullptr){ EXCEPT_INT("Something"); }
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);
	if(tempLoc == nullptr){ EXCEPT_INT("Something"); }

	// Syntax stuffs
	if(!check(TOKEN_CLOSEPARAN)){ EXCEPT_INT("Something"); }
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("A parantes after a function call is neccassary"); }

	// Returning the append_stmt
	return std::make_unique<append_stmt>(STA_APP, std::move(tempLoc), std::move(value));
}
std::unique_ptr<continue_stmt> MyStatementFactory::parseContinue_stmt()
{
	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("A parantes after a function call is neccassary"); }

	// Just returning the continue_stmt
	return std::make_unique<continue_stmt>(STA_CON);
}
std::unique_ptr<break_stmt> MyStatementFactory::parseBreak()
{
	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("A parantes after a function call is neccassary"); }

	// Just returning the break_stmt
	return std::make_unique<break_stmt>(STA_BRE);
}
std::unique_ptr<print_stmt> MyStatementFactory::parsePrint_stmt()
{
	// Extracting the single print Expression only for now
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> printExpr = fac.parse();
	if(printExpr == nullptr){ EXCEPT_INT("Something"); }

	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_INT("newline"); }

	// Returning the statement
	return std::make_unique<print_stmt>(STA_PRI, std::move(printExpr));
}
std::unique_ptr<if_stmt> MyStatementFactory::parseIf_stmt()
{
	// Finding the if condition
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> condition = fac.parse();
	if(condition == nullptr){ EXCEPT_INT("Something"); }
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_INT("Missing double colon in the if statement"); }

	// Findint the thenDo block
	std::unique_ptr<block_stmt> thenDo = parseBlock_stmt();

	// Finding the elseBLock if there are no elif blocks
	std::unique_ptr<else_stmt> elseBlock;
	if(check(TOKEN_ELIF)){
		std::unique_ptr<if_stmt> elifStmt = parseIf_stmt();
		std::unique_ptr<block_stmt> block = std::make_unique<block_stmt>(STA_BLO);
		block->addStmt(std::move(elifStmt));
		elseBlock = std::make_unique<else_stmt>(STA_ELS, std::move(block));
	}
	else if(check(TOKEN_ELSE)){
		elseBlock = parseElse_stmt();
	}

	// Returning the if_stmt
	return std::make_unique<if_stmt>(STA_IFF, std::move(condition), std::move(thenDo), std::move(elseBlock));
}
std::unique_ptr<else_stmt> MyStatementFactory::parseElse_stmt()
{
	std::unique_ptr<block_stmt> elseBlock;
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_INT("Something"); }
	elseBlock = parseBlock_stmt();
	return std::make_unique<else_stmt>(STA_ELS, std::move(elseBlock));
}
std::unique_ptr<while_stmt> MyStatementFactory::parseWhile_stmt()
{
	// Finding the while condition
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> condition = fac.parse();
	if(condition == nullptr){ EXCEPT_INT("Something"); }
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_INT("Missing double colon in the while statement"); }

	// Finding the thenDo block
	std::unique_ptr<block_stmt> thenDo = parseBlock_stmt();
	if(thenDo == nullptr){ EXCEPT_INT("something"); }

	// Outputing the statement
	return std::make_unique<while_stmt>(STA_WHI, std::move(condition), std::move(thenDo));
}


///////////////////////////////////////////////////////////////////////
/// GENERAL TOKEN MANIPULATION FUNCTION STUFFS
bool MyStatementFactory::check(int xTokenType)
{
	while(tokens.at(tokenIndicator).getTokenID() == TOKEN_SEMICOLON){
		// Ignoring semicolons
		advanceIndicator();
	}
	if(tokens.at(tokenIndicator).getTokenID() == xTokenType){
		// Advancing indicator safely
		advanceIndicator();
		return true;
	}
	return false;
}
bool MyStatementFactory::checkNoAdvance(int xTokenType)
{
	if(tokens.at(tokenIndicator).getTokenID() == xTokenType){
		// Checking but now advancing if there is the corrisponding token
		return true;
	}
	return false;
}
void MyStatementFactory::advanceIndicator()
{
	if(tokenIndicator < tokens.size()){
		tokenIndicator++;
	}
	else{
		EXCEPT_INT("Somethting");
	}
}
void MyStatementFactory::deAdvanceIndicator()
{
	if(tokenIndicator >= 1){
		tokenIndicator--;
	}
	else{
		EXCEPT_INT("Something");
	}
}
Token MyStatementFactory::previous()
{
	if(tokenIndicator >= tokens.size()){
		EXCEPT_INT("Tried to peek a token at a passed boundary");
	}
	if(tokenIndicator < 0){
		EXCEPT_INT("Tried to peek a token at a less than 0 boundary");
	}
	return tokens.at(tokenIndicator - 1);
}
Token MyStatementFactory::getToken()
{
	// Getting the token safely
	if(tokenIndicator < tokens.size()){
		int tempIndicator = tokenIndicator;
		advanceIndicator();
		return tokens.at(tempIndicator);
	}
	else{
		EXCEPT_INT("Something");
	}
}
Token MyStatementFactory::peek()
{
	// Getting the token safely without advancing the token indicator
	if(tokenIndicator < tokens.size()){
		return tokens.at(tokenIndicator);
	}
	else{
		EXCEPT_INT("The peeking at a non valid token indicator is not allowed");
	}
}