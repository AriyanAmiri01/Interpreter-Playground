// InterpreterPlayground.cpp
#include "MyFileOpener.h"
#include "MyException.h"
#include <exception>
#include <stdexcept>
#include <iostream>

int main(){
	// Error handling system
	try{
		// Testing to see if new commit can open a file
		std::string fileDir = "C:/Users/ariya/source/repos/Interpreter Playground/Interpreter Playground/FAIL_DivisionByZero.txt";
		MyFileOpener myFileOpener(fileDir);
		std::cout << "The content of the selected file is" << std::endl
			<<"[" << myFileOpener.getFile() << "]" << std::endl;
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