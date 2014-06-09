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
# define SAVE "./ressources/save/"

class AObject;
class Map
{
public:
  Map(int);
  Map(int, std::string &);
  Map(int, bool, ParticleEngine * = NULL);
  ~Map();
  Map(int, ParticleEngine *);
  AObject     *getCase(int, int) const;
  AObject     *getCase(std::pair<int, int> *) const;
  void        setSpawn(int nb);
  std::pair<int, int>   getSpawn();
  std::string     getName() const;
  void            setName(std::string &);
  void            addCube(int, int, type);
  void            addCube(int, int, AObject *);
  void            deleteCube(int, int);
  bool    check_pos(int x, int y);
  int     getSize() const;
  void    setSize(int);
  void    setMap(AObject **);
  void    setSpawn(std::vector<std::pair<int, int> > &);
  void    genereteName();
  std::pair<int, int> getSpawnPoint();
  bool    getState() const;

private:
  ParticleEngine  *_engine;
  std::vector<std::string> _paths;
  AObject       **_map;
  std::string   _name;
  int           _size_x;
  int           _size_y;
  std::vector<std::pair<int, int> >   _spawns;
  void          _deleteSide(int x, int y);
  void		      _outline();
  void          _drawWall();
  bool          _state;
};

#endif /* !MAP_HPP */
