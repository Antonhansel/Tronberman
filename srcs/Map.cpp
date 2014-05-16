//
// Map.cpp for Map in /home/apollo/rendu/cpp_bomberman
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Thu May  1 16:48:07 2014 ribeaud antonin
// Last update Sat May 10 22:50:48 2014 Mehdi Chouag
//

#include "Map.hpp"

Map::Map(int sizex, int sizey)
{
    _size_x = sizex;
    _size_y = sizey;
    _map = new AObject *[_size_x * _size_y];
    memset(_map, 0, (_size_x * _size_y) * sizeof(AObject *));
    _drawWall();
    _outline();
}

Map::~Map()
{
    for (int i = 0; i < _size_x * _size_y; ++i)
    {
        if (_map[i])
            delete _map[i];
    }
}

AObject     *Map::getCase(int x, int y) const
{
    if (x < 0 || x >= _size_x || y < 0 || y >= _size_y)
        return NULL;
    return _map[x * _size_x + y];
}

void Map::addCube(int x, int y, type blockType)
{
    std::pair<float, float>     pos;
    AObject     *tmp;

    if (x < 0 || x >= _size_x || y < 0 || y >= _size_y)
        return;
    if (_map[x * _size_x + y])
        deleteCube(x, y);
    tmp = create<Cube>();
    pos = std::make_pair(x, y);
    tmp->setType(blockType);
    tmp->setPos(pos);
    tmp->initialize();
    _map[x * _size_x + y] = tmp;
}

void Map::addCube(int x, int y, AObject *obj)
{
    std::pair<float, float>     pos;

    if (x < 0 || x >= _size_x || y < 0 || y >= _size_y)
        return;
    if (_map[x * _size_x + y])
        deleteCube(x, y);
    pos = std::make_pair(x, y);
    obj->setPos(pos);
    _map[x * _size_x + y] = obj;
}

void Map::deleteCube(int x, int y)
{
    if (x < 0 || x >= _size_x || y < 0 || y >= _size_y)
        return;
    delete _map[x * _size_x + y];
    _map[x * _size_x + y] = NULL;
}

void    Map::_outline()
{
    for (int y = 0; y < _size_y; y++)
    {
        addCube(0, y, BORDER);
        addCube(_size_x - 1, y, BORDER);
    }
    for (int x = 0; x < _size_x; x++)
    {
        addCube(x, 0, BORDER);
        addCube(x, _size_y - 1, BORDER);
    }
}

void    Map::_drawWall()
{
    srand(time(NULL));
    for (int y = 0; y <= _size_y; y++)
    {
        for (int x = 0; x <= _size_x; x++)
        {
            if (x % 2 == 0 && y % 2 == 0)
                addCube(x, y, BLOCK);
            else if ((rand() % 100) > 75)
                addCube(x, y, BLOCKD);
        }
    }
}

void    Map::_deleteSide(int x, int y)
{
    AObject *tmp;

    for (int i = x; i <= x + 1; i++)
    {
        for (int j = y; j <= y + 1; j++)
        {
            tmp = getCase(i, j);
            if (tmp && (tmp->getType() == BLOCKD || tmp->getType() == BLOCK))
                deleteCube(i, j);
        }
    }
}

std::vector<std::pair<int, int> >   &Map::setSpawn(int nb)
{
    int   x;
    int   y;

    srand(time(NULL));
    for (int i = 0; i < nb; i++)
    {
        x = rand() % (_size_x - 2) + 1;
        y = rand() % (_size_y - 2) + 1;
        if (x % 2 == 0)
            x--;
        if (y % 2 == 0)
            y--;
        _spawns.push_back(std::make_pair(x, y));
        _deleteSide(x, y);
    }
    return (_spawns);
}


std::vector<std::pair<int, int> >   &Map::getSpawn()
{
    return (_spawns);
}

int       Map::getY()
{
    return _size_y;
}

int       Map::getX()
{
    return _size_x;
}

void        Map::my_parseur(std::vector<int> &tab, std::string &str)
{
  unsigned int   x;
  unsigned int   y;
  int v;
  tab.clear();

  x = 0;
  y = 0;
  while (str[y])
  {
    if (str[y] == ' ')
    {
      std::istringstream buffer(str.substr(x, y - x + 1));
      buffer >> v;
      tab.push_back(v);
      x = y + 1;
    }
    y++;
  }
    std::istringstream buffer(str.substr(x, y - x + 1));
    buffer >> v;
    tab.push_back(v);
}

bool        Map::my_balise(std::string &in, std::string &out, std::string &str)
{
  unsigned int pos = str.find(in) + in.length();
  unsigned int pos2 = str.find(out);

  if (pos2 != std::string::npos)
    str = str.substr(pos, pos2 - pos);
  else
    str = str.substr(pos);
  return (true);
}

void    Map::load_size(std::list<std::string> &file)
{
    std::vector<int> tab;
    std::string       str;
    std::string       in = "<size>";
    std::string       out = "</size>";

    str = my_balise(in, out, file.front());
    my_parseur(tab, file.front());
    _size_x = tab.back();
    _size_y = tab.back();
    delete _map;
    _map = new AObject *[_size_x * _size_y];
    memset(_map, 0, (_size_x * _size_y) * sizeof(AObject *));
    while (!_spawns.empty())
       _spawns.pop_back();

  file.pop_front();
}

void    Map::load_case(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<case>";
  std::string       out = "</case>";
  type _type;
  int x;
  int y;
  int t;

  str = my_balise(in, out, file.front());
  my_parseur(tab, file.front());
  t = tab.back();
  tab.pop_back();
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  _type = (type)t;
  addCube(x, y, _type);
  file.pop_front();
}

void    Map::load_spawn(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<spawn>";
  std::string       out = "</spawn>";
  int x;
  int y;

  str = my_balise(in, out, file.front());
  my_parseur(tab, file.front());
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  tab.pop_back();
  _spawns.push_back(std::make_pair(x, y));
  _deleteSide(x, y);
  file.pop_front();
}

void    Map::load_map(std::string &file_name)
{
  std::list<std::string>  file;
  std::string             str;
  std::ifstream           infile(file_name.c_str());
  std::vector<int>  tab;

  while (std::getline(infile, str))
    file.push_back(str);
  if (file.size() > 0)
  {
    while (file.front().find("<map") != std::string::npos
          && file.size() > 0)
      file.pop_back();

    while (file.front().find("</map") == std::string::npos
          && file.size() > 0)
    {
      if (file.front().find("<size>") != std::string::npos)
        load_size(file);
      else if (file.front().find("<case>") != std::string::npos)
        load_case(file);
      else if (file.front().find("<spawn>") != std::string::npos)
        load_spawn(file);
      else
        file.pop_front();
    }
  }
  else
    std::cout << "The map is not found." << std::endl;
}