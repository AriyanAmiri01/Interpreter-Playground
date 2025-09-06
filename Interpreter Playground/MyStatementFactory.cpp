// MyMyStatementFactory.cpp
#include "MyStatementFactory.h"


///////////////////////////////////////////////////////////////////////
/// GENERAL STATEMENT STUFFS
MyStatementFactory::MyStatementFactory(std::vector<Token>& xTokens)
	:
	tokenIndicator(0),
	tokens(xTokens)
{
}


///////////////////////////////////////////////////////////////////////
/// PARSE FUNCTIONS STUFFS
std::unique_ptr<stmt> MyStatementFactory::FindStatement()
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
				return ParseList_stmt(varName);
			}else
			{
				return ParseAssign_stmt(varName);
			}
		}else if(check(TOKEN_DOT))
		{
			return ParseAppend_stmt(varName);
		}
		EXCEPT_COD_NOLINE("after a identifier a dot or a = token is neccesasary");
		return nullptr;
	}
	else if(check(TOKEN_BREAK))
	{
		return ParseBreak();
	}
	else if(check(TOKEN_CONTINUE))
	{
		return ParseContinue_stmt();
	}
	else if(check(TOKEN_PRINT))
	{
		return ParsePrint_stmt();
	}
	else if(check(TOKEN_IF))
	{
		return ParseIf_stmt();
	}
	else if(check(TOKEN_WHILE))
	{
		return ParseWhile_stmt();
	}
	else if(check(TOKEN_NEWLINE)){
		return FindStatement();
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
		EXCEPT_COD_NOLINE("There is no type of statement corrisponding to this token");
		return nullptr;
	}
}
std::unique_ptr<block_stmt> MyStatementFactory::ParseBlock_stmt()
{
	// The container of the block_stmt
	std::unique_ptr<block_stmt> block = std::make_unique<block_stmt>(STA_BLO);

	// Getting into the block
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("A new line after the if condition is neccessary"); }
	if(!check(TOKEN_INDENT)){ EXCEPT_COD_NOLINE("A INDENT after the if condition is neccessary"); }

	// Looping based on the block scope which gets closed after a dedent
	while(!check(TOKEN_DEDENT)){
		// Adding current statements to the block_stmt
		auto temp = FindStatement();
		if(temp != nullptr){
			block->addStmt(std::move(temp));
		}
	}
	return block;
}
std::unique_ptr<assignment_stmt> MyStatementFactory::ParseAssign_stmt(std::string xVarName)
{
	// If it is assignment_stmt
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> value = fac.parse();

	// Creating the variable LocExpression
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	#ifndef NDEBUG
	if(tempId == nullptr){ EXCEPT_INT("Interpreter failed to create a identifier for the variabnle"); }
	#endif
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);
	#ifndef NDEBUG
	if(tempLoc == nullptr){ EXCEPT_INT("Interpreter failed to create a locExpression for the variabnle"); }
	#endif
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("A new line at the end of assignment_stmt is neccesary"); }

	return std::make_unique<assignment_stmt>(STA_ASS, std::move(tempLoc), std::move(value));
}
std::unique_ptr<list_stmt> MyStatementFactory::ParseList_stmt(std::string xVarName)
{
	// If it is a list_stmt
	if(!check(TOKEN_OPENPARAN)){ EXCEPT_COD_NOLINE("Something"); }

	// For now the interpreter only allows list declaration
	if(!check(TOKEN_CLOSEPARAN)){ EXCEPT_COD_NOLINE("Something"); }
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("Something"); }
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);

	#ifndef NDEBUG
	if(tempLoc == nullptr){ EXCEPT_INT("Interpreter failed to create a locExpression for the variabnle"); }
	#endif

	return std::make_unique<list_stmt>(STA_ASS, std::move(tempLoc));
}
std::unique_ptr<append_stmt> MyStatementFactory::ParseAppend_stmt(std::string xVarName)
{
	// Syntax stuffs
	if(!check(TOKEN_APPE)){ EXCEPT_COD_NOLINE("Only append function has been defined into the interpreter"); }
	if(!check(TOKEN_OPENPARAN)){ EXCEPT_COD_NOLINE("A parantes after a function call is neccassary"); }

	// Finding the append Expression
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> value = fac.parse();
	#ifndef NDEBUG
	if(value == nullptr){ EXCEPT_INT("Interpreter failed to find the value of the expression"); }
	#endif 
	auto tempId = std::make_unique<identifier>(xVarName, -5);
	#ifndef NDEBUG
	if(tempId == nullptr){ EXCEPT_INT("Interpreter failed to to create an identifier"); }
	#endif 
	auto tempLoc = std::make_unique<locExpression>(std::move(tempId), nullptr);
	#ifndef NDEBUG
	if(tempLoc == nullptr){ EXCEPT_INT("Interpreter failed to create a locExpression"); }
	#endif 

	// Syntax stuffs
	if(!check(TOKEN_CLOSEPARAN)){ EXCEPT_COD_NOLINE("A close paranthesis after after the append() is needed"); }
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("A parantes after a function call is neccassary"); }

	// Returning the append_stmt
	return std::make_unique<append_stmt>(STA_APP, std::move(tempLoc), std::move(value));
}
std::unique_ptr<continue_stmt> MyStatementFactory::ParseContinue_stmt()
{
	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("A parantes after a function call is neccassary"); }

	// Just returning the continue_stmt
	return std::make_unique<continue_stmt>(STA_CON);
}
std::unique_ptr<break_stmt> MyStatementFactory::ParseBreak()
{
	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("A parantes after a function call is neccassary"); }

	// Just returning the break_stmt
	return std::make_unique<break_stmt>(STA_BRE);
}
std::unique_ptr<print_stmt> MyStatementFactory::ParsePrint_stmt()
{
	// Extracting the single print Expression only for now
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> printExpr = fac.parse();
	#ifndef NDEBUG
	if(printExpr == nullptr){ EXCEPT_INT("Failed to find the print statement"); }
	#endif

	// checking the new line at the end of the statement
	if(!check(TOKEN_NEWLINE)){ EXCEPT_COD_NOLINE("newline"); }

	// Returning the statement
	return std::make_unique<print_stmt>(STA_PRI, std::move(printExpr));
}
std::unique_ptr<if_stmt> MyStatementFactory::ParseIf_stmt()
{
	// Finding the if condition
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> condition = fac.parse();
	#ifndef NDEBUG
	if(condition == nullptr){ EXCEPT_INT("Something"); }
	#endif
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_COD_NOLINE("Missing double colon in the if statement"); }

	// Findint the thenDo block
	std::unique_ptr<block_stmt> thenDo = ParseBlock_stmt();

	// Finding the elseBLock if there are no elif blocks
	std::unique_ptr<else_stmt> elseBlock;
	if(check(TOKEN_ELIF)){
		std::unique_ptr<if_stmt> elifStmt = ParseIf_stmt();
		std::unique_ptr<block_stmt> block = std::make_unique<block_stmt>(STA_BLO);
		block->addStmt(std::move(elifStmt));
		elseBlock = std::make_unique<else_stmt>(STA_ELS, std::move(block));
	}
	else if(check(TOKEN_ELSE)){
		elseBlock = ParseElse_stmt();
	}

	// Returning the if_stmt
	return std::make_unique<if_stmt>(STA_IFF, std::move(condition), std::move(thenDo), std::move(elseBlock));
}
std::unique_ptr<else_stmt> MyStatementFactory::ParseElse_stmt()
{
	std::unique_ptr<block_stmt> elseBlock;
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_INT("Something"); }
	elseBlock = ParseBlock_stmt();
	return std::make_unique<else_stmt>(STA_ELS, std::move(elseBlock));
}
std::unique_ptr<while_stmt> MyStatementFactory::ParseWhile_stmt()
{
	// Finding the while condition
	ExpressionFactory fac(tokens, tokenIndicator);
	std::unique_ptr<expr> condition = fac.parse();
	#ifndef NDEBUG
	if(condition == nullptr){ EXCEPT_INT("Interpreter failed to find condition of the expression"); }
	#endif
	if(!check(TOKON_DOUBLECOLON)){ EXCEPT_COD_NOLINE("Missing double colon in the while statement"); }

	// Finding the thenDo block
	std::unique_ptr<block_stmt> thenDo = ParseBlock_stmt();
	#ifndef NDEBUG
	if(thenDo == nullptr){ EXCEPT_INT("Interpreter failed to find the thenDo statements"); }
	#endif

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
	if(tokenIndicator < static_cast<signed>(tokens.size())){
		tokenIndicator++;
	}
	#ifndef NDEBUG
	else{
		EXCEPT_INT("Interpreter failed to advance the token indicator because of the memory boundary");
	}
	#endif
}
void MyStatementFactory::deAdvanceIndicator()
{
	if(tokenIndicator >= 1){
		tokenIndicator--;
	}
	else{
		#ifndef NDEBUG
		EXCEPT_INT("Something");
		#endif 
	}
}
Token MyStatementFactory::previous()
{
	if(tokenIndicator >= tokens.size()){
		#ifndef NDEBUG
		EXCEPT_INT("Tried to peek a token at a passed boundary");
		#endif 
	}
	if(tokenIndicator < 0){
		#ifndef NDEBUG
		EXCEPT_INT("Tried to peek a token at a less than 0 boundary");
		#endif 
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
		#ifndef NDEBUG
		EXCEPT_INT("Something");
		#endif 
	}
}
Token MyStatementFactory::peek()
{
	// Getting the token safely without advancing the token indicator
	if(tokenIndicator < tokens.size()){
		return tokens.at(tokenIndicator);
	}
	else{
		#ifndef NDEBUG
		EXCEPT_INT("The peeking at a non valid token indicator is not allowed");
		#endif 
	}
}