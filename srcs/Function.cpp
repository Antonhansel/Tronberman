/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Mon May 19 18:23:32 2014 ribeaud antonin
*/

#include "Function.hpp"

int  Function::convToInt(const std::string &s)
{
  std::istringstream iss(s);
  int        val = 0;

  iss >> val;
  return (val);
}

std::string  &Function::convToString(std::string &s, const int i)
{
  std::stringstream ss;

  ss << i;
  s = ss.str();
  return (s);
}
