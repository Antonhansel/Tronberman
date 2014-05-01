#include "Case.hpp"

Case::Case(const int& x, const int& y, const Case_type& type) :
	pos_x(x), pos_y(y), _type(type)
{}

Case::~Case()
{}

int					Case::getPosx()
{
	return (pos_x);
}

int					Case::getPosy()
{
	return (pos_y);
}

Case_type			Case::getTypeCase()
{
	return (_type);
}
