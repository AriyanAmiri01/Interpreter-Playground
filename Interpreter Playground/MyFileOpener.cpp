// MyFileOpener.cpp
#include "MyFileOpener.h"


/////////////////////////////////////////////////////////////////
///	FILE OPENER IMPLEMENTATION STUFFS
MyFileOpener::MyFileOpener(const std::string& fileDir)
{
	// Opening the file
	std::ifstream fin;
	fin.open(fileDir, std::ios::in);

	//Checking if the file has been opened or not
	if(!fin){
		throw std::runtime_error("File not fined: " + fileDir);
	}

	// Creating the temporary oss
	std::ostringstream oss;

	// Reading the file
	oss << fin.rdbuf();

	// Writing the file
	file = oss.str();
}
MyFileOpener::MyFileOpener(const MyFileOpener& xFile) noexcept
	:
	file(xFile.file)
{
}
MyFileOpener::MyFileOpener(MyFileOpener&& xFile) noexcept
	:
	file(std::move(xFile.file))
{
}
std::string MyFileOpener::getFile() const noexcept
{
	return file;
}