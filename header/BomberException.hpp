//
// BomberException.hpp for bomberman in /home/geekuillaume/Dropbox/Epitech/tek2/current/cpp_bomberman/header/BomberException.hpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Jan 10 09:07:44 2014 guillaume besson
//

#pragma once

#include <string>
#include <exception>

class BomberException : public std::exception {
public:
  BomberException(const std::string what) throw() : _what(what) {};
  ~BomberException() throw() {};
  const char* what() const throw() {return _what.c_str();};
private:
    std::string _what;
};
