#pragma once
// MyException.h
#include <exception>
#include <stdexcept>
#include <sstream>
#include <string>


class MyException : public std::exception
{
public:
	MyException(int xLine, std::string xFile, std::string excptionInfo, std::string xType = "MyException");
	const char* what() const noexcept override;
	int getLine() const noexcept;
	const std::string getFile() const noexcept;
private:
	int line;
	std::string file;
	std::string type;
	std::string description;
protected:
	mutable std::string whatBuffer;
};


// Creating some macros for easier exception handling
#define EXCEPT_INT(xWhat) throw (MyException(__LINE__, __FILE__, xWhat, "InterpretExcpetion"))
#define EXCEPT_COD(xLine,xFile,xWhat) throw (MyException(xLine, xFile, xWhat, "SourceCodeException"))
#define EXCEPT_COD_NOLINE(xWhat) throw (MyException(__LINE__, __FILE__, xWhat, "SourceCodeNoLineException"))
#define EXCEPT_TOKEN(x) do { INFO_TOKEN(); throw MyException(__LINE__, __FILE__, x, "TokenException"); } while(0)


// Creating some macros for fast access to the internal elements while debugging 
#define INFO_STATE() std::cout<<"[StatementID:" << i->stmtType <<"]" <<std::endl
#define INFO_TOKEN() std::cout<<"[TokenID:" << tokenIndicator <<"||TokenString:"<<tokens.at(tokenIndicator).getTokenString() <<"]" <<std::endl
#define INFO_EXPR(exp) {std::cout << std::endl << "Expreession: " << std::endl;exprVisitor visArg;exp->accept(visArg);std::cout << std::endl << "=================== " << std::endl << std::endl; }