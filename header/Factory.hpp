//
// Factory.hpp for Factory in /home/chouag_m/rendu/old
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat May  3 18:31:22 2014 Mehdi Chouag
// Last update Sun May  4 00:49:05 2014 Mehdi Chouag
//

#ifndef FACTORY_HPP_
# define FACTORY_HPP_

#include "Cube.hpp"
#include "Char.hpp"
#include "Mybot.hpp"

template<typename T>
T	*create()
{
  return (new T);
}

#endif /* !FACTORY_HPP_ */
