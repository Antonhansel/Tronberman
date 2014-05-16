#ifndef MAP_HPP
# define MAP_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <map>
# include <stdlib.h>
# include <utility>
# include "Factory.hpp"

class AObject;

class Map
{
public:
  Map(int, int);
  ~Map();

  AObject     *getCase(int, int) const;
  std::vector<std::pair<int, int> >   &setSpawn(int nb);
  std::vector<std::pair<int, int> >   &getSpawn();
  void    addCube(int, int, type);
  void    addCube(int, int, AObject *);
  void    deleteCube(int, int);
  int     getX();
  int     getY();
  bool    my_balise(std::string &, std::string &, std::string &);
  void    my_parseur(std::vector<int> &, std::string &);
  void    load_spawn(std::list<std::string> &);
  void    load_case(std::list<std::string> &);
  void    load_size(std::list<std::string> &);
  void    load_map(std::string &);
private:
  AObject **_map;
  int     _size_x;
  int     _size_y;
  std::vector<std::pair<int, int> >   _spawns;
  void    _deleteSide(int x, int y);
  void		_outline();
  void    _drawWall();
};

#endif /* !MAP_HPP */
