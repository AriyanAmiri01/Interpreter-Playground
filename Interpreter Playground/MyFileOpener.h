#pragma once
// MyFileOpener.h
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>


class MyFileOpener
{
public:
	MyFileOpener(const std::string& fileDir);
	~MyFileOpener() = default;
	MyFileOpener(const MyFileOpener& xFile) noexcept;
	MyFileOpener& operator=(const MyFileOpener& xFile) = delete;
	MyFileOpener(MyFileOpener&& f) noexcept;
	MyFileOpener& operator=(MyFileOpener&&) = delete;
public:
	std::string getFile() const noexcept;
	std::string& getFileRef() noexcept;
private:
	std::string file;
};