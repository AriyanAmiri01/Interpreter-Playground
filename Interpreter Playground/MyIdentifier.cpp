// Identifier.cpp
#include "MyIdentifier.h"


/////////////////////////////////////////////////////////////////
///	IDENTIFIER CLASS STUFF
identifier::identifier(std::string xName, int xScope)
	:
	name(xName),
	scope(xScope)
{
}
bool identifier::operator<(const identifier& xRight) const
{
	return name < xRight.name;
}
std::unique_ptr<identifier> identifier::clone() const
{
	return std::make_unique<identifier>(name, scope);
}