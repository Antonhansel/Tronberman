#ifndef MAP_HPP
# define MAP_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <map>
# include <stdlib.h>
# include <utility>
# include "AObject.hpp"
# include "Factory.hpp"

class Map
{
public:
  Map(const int&, const int&, std::map< std::pair<float, float>, AObject * > &);
  Map(const std::string&);

  void				outline();
  void				spawnBot();
  void				drawWall();
  bool				spawnBotChecking(const int&, const int&);
  bool				isEmpty(const int&, const int&);
  std::map< std::pair<float, float>, AObject *> &getMap();
  ~Map();
private:
  std::map< std::pair<float, float>, AObject *> cases;
  int					size_x;
  int					size_y;
};

#endif /* !MAP_HPP */
