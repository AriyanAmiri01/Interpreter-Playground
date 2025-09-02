// MyParser.cpp
#include "MyParser.h"


///////////////////////////////////////////////////////////////////////
/// SYNTATICAL ANALYSER STUFFS
MyParser::MyParser(int xTokenIndicator, std::vector<Token> xTokens)
	:
	tokenIndicator(xTokenIndicator),
	tokens(xTokens),
	sf(xTokenIndicator, xTokens)
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
	// Looping through all the tokens and parisng until EOF
	while(sf.peek().getTokenID() != TOKEN_EOF){
		AST.push_back(std::move(sf.findStatement()));
	}
}

void MyParser::testAST()
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
