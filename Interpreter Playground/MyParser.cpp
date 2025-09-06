// MyParser.cpp
#include "MyParser.h"


///////////////////////////////////////////////////////////////////////
/// SYNTATICAL ANALYSER STUFFS
MyParser::MyParser(std::vector<Token>& xTokens)
	:
	tokens(xTokens)
{
	// Just initializing stuffs
	if(tokens.empty()){
		EXCEPT_INT("There is no token found on the token buffer");
	}
}


///////////////////////////////////////////////////////////////////////
/// ABSTRACT SYNTAX TREE STUFFS 
void MyParser::ASTCreator()
{
	// The class used for parsing the statements
	MyStatementFactory sf(tokens);

	// Looping through all the tokens and parisng until EOF
	while(sf.peek().getTokenID() != TOKEN_EOF){
		AST.push_back(std::move(sf.FindStatement()));
	}
}

void MyParser::TestAST()
{
	std::cout
		<< std::endl
		<< "___________________________________"
		<< "The result of the testAst:" << std::endl;
	for(auto const& i : AST){
		i->testStmt();
	}
	std::cout 
		<< std::endl
		<< "___________________________________" 
		<<std::endl;
}