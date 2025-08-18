// InterpreterPlayground.cpp
#include <exception>
#include <stdexcept>
#include <iostream>

int main(){
	// Error handling system
	try{

	}
	catch(const std::exception& e){
		std::cerr << "Exception:" << e.what() << std::endl;
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