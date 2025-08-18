// MyException.cpp
#include "MyException.h"


////////////////////////////////////////////////////////////////////////
/// EXCEPTION CLASS STUFFS
MyException::MyException(int xLine, std::string xFile, std::string excptionInfo, std::string xType)
	:
	line(xLine),
	file(xFile),
	description(excptionInfo),
	type(xType)
{
}
const char* MyException::what() const noexcept
{
	std::ostringstream oss;
	oss << "[The type:" << type << "]" << std::endl
		<< "[File:" << file << "]" << std::endl
		<< "[Line:" << line << "]" << std::endl
		<< "[Description:]" << std::endl
		<< "[\"" << description << "\"]" << std::endl;
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}
int MyException::getLine() const noexcept
{
	return line;
}
const std::string MyException::getFile() const noexcept
{
	return file;
}