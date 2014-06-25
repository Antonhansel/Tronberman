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
  Map(const int);
  Map(const int, std::string &);
  Map(const int, const bool, ParticleEngine * = NULL);
  ~Map();
  Map(const int, ParticleEngine *);
  AObject     *getCase(const int, const int) const;
  AObject     *getCase(std::pair<int, int> *) const;
  void        setSpawn(const int);
  std::pair<int, int>   getSpawn();
  std::string     getName() const;
  void            setName(std::string const &);
  void            addCube(const int, const int, const type);
  void            addCube(const int, const int, AObject *);
  void            deleteCube(const int, const int);
  bool    check_pos(const int, const int) const;
  int     getSize() const;
  void    setSize(const int);
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
