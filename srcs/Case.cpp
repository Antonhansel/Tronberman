//
// Case.cpp for Case in /home/apollo/rendu/cpp_bomberman
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Thu May  1 16:47:33 2014 ribeaud antonin
// Last update Thu May  1 16:47:39 2014 ribeaud antonin
//

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
