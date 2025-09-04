// MySemanticAnalyzer.cpp
#include "MySemanticAnalyzer.h"
#include <stdexcept>
#include <iostream>


/////////////////////////////////////////////////////////////////
///	SEMANTIC ANALYSER STUFF
MySemanticAnalyzer::MySemanticAnalyzer(std::vector<std::unique_ptr<stmt>>&& xAST) {
	for(auto& e : xAST) {

		AST.push_back(std::move(e));
	}
}
int floor_div(int a, int b) {
	return (a - (a % b)) / b - ((a % b != 0) && ((a < 0) != (b < 0)));
}

/////////////////////////////////////////////////////////////////
///	ACTUAL EXECUTION AND ANALYSIS STUFFS
void MySemanticAnalyzer::interpret()
{
	for(auto& e : AST){
		e->accept(*this);
	}
}
void MySemanticAnalyzer::execute(stmt& s)
{
	// This function is used as a abstract class
	EXCEPT_INT("Abstract class does not have any execute function");
}
void MySemanticAnalyzer::execute(block_stmt& s)
{
	// We are in a new scope 
	currentScopeNum++;

	// Looping through all the statements inside the block statement 
	for(auto& e : s.statements){
		e->accept(*this);
	}

	// Clean up entries in symbolTable that belong to the current scope
	for(auto it = symbolTable.begin(); it != symbolTable.end(); ) {
		if(it->first.scope == currentScopeNum) {
			it = symbolTable.erase(it); // erase returns the next iterator
		}
		else {
			++it;
		}
	}

	// Clean up entries in listSymbolTable for the current scope
	for(auto it = listSymbolTable.begin(); it != listSymbolTable.end(); ) {
		if(it->first.scope == currentScopeNum) {
			it = listSymbolTable.erase(it);
		}
		else {
			++it;
		}
	}
	currentScopeNum--;
}
void MySemanticAnalyzer::execute(simple_stmt& s)
{
	// This class is used as a abstract class
	EXCEPT_INT("the class \"stmt\" has only been defined as an interface, no execute() function has been found");
}
void MySemanticAnalyzer::execute(assignment_stmt& s)
{
	// We fetch the id of the locExpression for assignment 
	std::unique_ptr<identifier> variable = s.location->id->clone();
	if(variable == nullptr){ EXCEPT_INT("Something"); }

	// We first fetch the expression pointer to the factory
	std::unique_ptr<expr> thisExpr = s.assignValue->clone();
	if(thisExpr == nullptr){ EXCEPT_INT(" something"); }

	// We execute that expression so we get the final value to be assigned
	valueExpression assignValue = thisExpr->accept(*this);
	

	// We update symbol table
	if(symbolTable.contains(*variable)){
		// If it contains it we only assign it
		symbolTable.at(*variable) = assignValue;
	}
	else{
		// We emplace the new variable into the symbol table
		std::string varName = variable->name;
		identifier lastId(varName, currentScopeNum);
		symbolTable.emplace(lastId, assignValue);
	}
}
void MySemanticAnalyzer::execute(list_stmt& s)
{
	// We fetch the id of the locExpression for assignment 
	std::unique_ptr<identifier> variable = std::move(s.location->id->clone());

	if(listSymbolTable.contains(*variable)){
		// If it contains it we only throw something
		EXCEPT_INT("can not declare one list twice");
	}
	else{
		// We add the new list with its dummy vector as the content
		std::vector<valueExpression> dummyVector;
		listSymbolTable.emplace(*variable, std::move(dummyVector));
	}
}
void MySemanticAnalyzer::execute(append_stmt& s)
{
	// We fetch the id of the locExpression for assignment 
	std::unique_ptr<identifier> variable = s.location->id->clone();

	// We execute the valueExpression that is about to be assingned
	valueExpression assignValue = s.expression->accept(*this);

	// Time to append
	if(listSymbolTable.contains(*variable)){
		// We push back the new valueExpression to the vector
		listSymbolTable.at(*variable).push_back(assignValue);
	}
	else{
		// The identifier was not on the symbol table so we throw
		EXCEPT_INT("the identifier was not on the symbol table");
	}
}
void MySemanticAnalyzer::execute(continue_stmt& s)
{
	if(loopDepth < 1){ EXCEPT_INT("tried to call continue without a loop"); }
	loopDepth--;
}
void MySemanticAnalyzer::execute(break_stmt& s)
{
	if(loopDepth < 1){ EXCEPT_INT("tried to call continue without a loop"); }
	loopDepth--;
}
void MySemanticAnalyzer::execute(print_stmt& s)
{
	// Getting the value that is about to be printed
	valueExpression printValue = s.expression->accept(*this);
	switch(printValue.valType){
	case(VAL_NDE):
		{
			std::cout << "null";
			break;
		}
	case(VAL_BOO):
		{
			if(printValue.boolValue == 0){
				std::cout << "False";
			}
			else{
				std::cout << "True";
			}
			break;
		}
	case(VAL_INT):
		{
			std::cout << printValue.numberValue;
			break;
		}
	case(VAL_STR):
		{
			std::cout << printValue.stringValue;
			break;
		}
	default:
		{
			EXCEPT_INT("Something");
			break;
		}
	}
}
void MySemanticAnalyzer::execute(compound_stmt& s)
{
	EXCEPT_INT("Something");
}
void MySemanticAnalyzer::execute(if_stmt& s)
{
	// Extracting the if condition 
	valueExpression condition = s.condition->accept(*this);

	// Extracting thenDo block
	if(condition.getBoolValue()){
		s.thenBlock->accept(*this);
	}
	else if(s.elseBlock){
		s.elseBlock->accept(*this);
	}
}
void MySemanticAnalyzer::execute(else_stmt& s)
{
	// We execute this as a thenBlock
	s.thenBlock->accept(*this);
}
void MySemanticAnalyzer::execute(while_stmt& s)
{
	// Incrementing the loopDepth
	loopDepth++;

	// Extra error checking
	if(!s.condition) { EXCEPT_INT("The condition of the while loop has been null"); }

	// The main while loop of while_stmt
	int breakTrigger = 0;
	while(s.condition->accept(*this).getBoolValue()){
		// Checking if the previouse cycle has called break
		if(breakTrigger == 1){
			break;
		}

		// Looping through all the stmt in the thenDo
		for(auto& i : s.thenBlock){
			// Checking if it is for flow controll
			if(i->stmtType == STA_CON){
				// Checking if it is continue
				break;
			}
			if(i->stmtType == STA_BRE){
				// Checking if it is break
				breakTrigger = 1;
				break;
			}

			// Finally executing the statements
			i->accept(*this);
		}
	}
	loopDepth--;
}
valueExpression MySemanticAnalyzer::execute(expr& e)
{
	INFO_EXPR(e.clone());
	std::cout << e.expType;
	EXCEPT_INT("Abstract class can not execute anything");
}
valueExpression MySemanticAnalyzer::execute(valueExpression& c)
{
	return c;
}
valueExpression MySemanticAnalyzer::execute(locExpression& c)
{
	// Loc expression contains a expression, so we execute that
	if(symbolTable.contains(*c.id)){
		return symbolTable.at(*c.id);
	}
	else{
		EXCEPT_INT("Something");
	}
}
valueExpression MySemanticAnalyzer::execute(orExpression& c)
{
	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_OR):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first.boolValue || second.boolValue;
			return v;
		}
	default:
		EXCEPT_INT("The inserted binaryExpression has not been defined");
	}
}
valueExpression MySemanticAnalyzer::execute(andExpression& c)
{

	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_AND):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first.boolValue && second.boolValue;
			return v;
		}
	default:
		EXCEPT_INT("The inserted binaryExpression has not been defined");
	}
}
valueExpression MySemanticAnalyzer::execute(numExpression& c)
{

	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_PLU):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = first.numberValue + second.numberValue;
			return v;
		}
	case(EXP_MIN):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = first.numberValue - second.numberValue;
			return v;
		}
	default:
		EXCEPT_INT("The inserted statement in to the executing pipeline is not a numExpression");
	}
}
valueExpression MySemanticAnalyzer::execute(termExpression& c)
{

	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);


	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_MUL):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = first.numberValue * second.numberValue;
			return v;
		}
	case(EXP_DIV):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = first.numberValue / second.numberValue;
			return v;
		}
	case(EXP_MOD):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = first.numberValue % second.numberValue;
			return v;
		}
	case(EXP_EPN):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = pow(first.numberValue, second.numberValue);
			return v;
		}
	case(EXP_FLD):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = floor_div(first.numberValue, second.numberValue);
			return v;
		}
	default:
		EXCEPT_INT("The inserted statement in to the executing pipeline is not a numExpression");
	}
}
valueExpression MySemanticAnalyzer::execute(equalityExpression& c)
{
	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_EQU):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first == second;
			return v;
		}
	case(EXP_NEQ):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first != second;
			return v;
		}
	default:
		EXCEPT_INT("The inserted binaryExpression has not been defined");
	}
}
valueExpression MySemanticAnalyzer::execute(relExpression& c)
{
	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.left->accept(*this);
	valueExpression second = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_GRE):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first > second;
			return v;
		}
	case(EXP_GEQ):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first >= second;
			return v;
		}
	case(EXP_LES):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first < second;
			return v;
		}
	case(EXP_LEE):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = first <= second;
			return v;
		}
	default:
		EXCEPT_INT("The inserted binaryExpression has not been defined");
	}
}
valueExpression MySemanticAnalyzer::execute(unaryExpression& c)
{
	// We execute the left and right expression to get the second and first valueExpression
	valueExpression first = c.right->accept(*this);

	// Time to output the result of two expression as a valueExpression
	switch(c.expType)
	{
	case(EXP_NEG):
		{
			valueExpression v;
			v.valType = VAL_INT;
			v.numberValue = -first.numberValue;
			return v;
		}
	case(EXP_NOT):
		{
			valueExpression v;
			v.valType = VAL_BOO;
			v.boolValue = !first.getBoolValue();
			return v;
		}
	case(EXP_PLU):
		{
			valueExpression v;
			v.valType = first.valType;
			v.numberValue = +first.numberValue;
			return v;
		}
	default:
		EXCEPT_INT("The inserted unary value has not been defined yet in the system");
	}
}
valueExpression MySemanticAnalyzer::execute(factorExpression& c)
{
	return c.value->accept(*this);
}
valueExpression MySemanticAnalyzer::execute(nullExpr& c)
{
	// I am not really sure about this...
	valueExpression v;
	v.valType = VAL_STR;
	v.stringValue = "null";
	return v;
}