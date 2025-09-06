// InterpreterPlayground.cpp
#include "MyFileOpener.h"
#include "MyException.h"
#include "MyLexor.h"
#include "MyParser.h"
#include "MySemanticAnalyzer.h"
#include <exception>
#include <stdexcept>
#include <iostream>

int main(){
	// Error handling system
	try{

		// Testing to see if new commit can open a file
		std::string fileDir = "C:/Users/ariya/source/repos/Interpreter Playground/Interpreter Playground/VettoriTest/PASS_Factorial.txt";
		MyFileOpener myFileOpener(fileDir);

		// Lexing the file
		MyLexor myLexor(myFileOpener.getFile());
		myLexor.Tokenize();
		myLexor.TestTokens();

		// Parsing the file
		MyParser myParser(myLexor.GetTokensRef());
		myParser.ASTCreator();
		myParser.TestAST();

		// Anylizing the AST
		MySemanticAnalyzer mySemanticalAnalyzer(std::move(myParser.AST));
		mySemanticalAnalyzer.interpret();
	}
	catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch(...){
		std::cerr << "Unknown error occurred.\n";
		return 1;
	}

	// [TEMP] : for test purposses
	char c;
	do {
		std::cout << "Press 'e' to continue...\n";
		std::cin >> c;
	} while(c != 'e');

	return 0;
}