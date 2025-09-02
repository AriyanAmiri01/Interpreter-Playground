// Identifier.h
#pragma once
#include <string>
#include <memory>


class identifier
{
public:
	explicit identifier(std::string xName, int xScope);
public:
	bool operator<(const identifier& xRight) const;
	std::unique_ptr<identifier> clone() const;
public:
	std::string name;
	int scope;
};

