#ifndef MAP_HPP
# define MAP_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <map>
# include <cstdlib>
# include <utility>
# include "Factory.hpp"

# define PATH "./ressources/maps/"

class AObject;

class Map
{
public:
  Map(int);
  ~Map();

  AObject     *getCase(int, int) const;
  std::vector<std::pair<int, int> >   &setSpawn(int nb);
  std::vector<std::pair<int, int> >   getSpawn() const;
  std::string     getName() const;
  void            addCube(int, int, type);
  void            addCube(int, int, AObject *);
  void            deleteCube(int, int);
  bool    check_pos(int x, int y);
  int     getSize() const;
  void    setSize(int);
  void    setMap(AObject **);
  AObject **getMap() const;
  void    setSpawn(std::vector<std::pair<int, int> > &);
  void    genereteName();

private:
  std::vector<std::string> _paths;
  AObject       **_map;
  std::string   _name;
  int           _size_x;
  int           _size_y;
  std::vector<std::pair<int, int> >   _spawns;
  void          _deleteSide(int x, int y);
  void		      _outline();
  void          _drawWall();
};

#endif /* !MAP_HPP */
