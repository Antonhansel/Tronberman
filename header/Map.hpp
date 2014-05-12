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
  void    addCube(int, int, type);
  void    addCube(int, int, AObject *);
  void    deleteCube(int, int);
private:
  std::vector<AObject *>  _map;
  int     _size_x;
  int     _size_y;
  std::vector<std::pair<int, int> >   _spawns;
  void    _deleteSide(int x, int y);
  void		_outline();
  void    _drawWall();
};

#endif /* !MAP_HPP */
