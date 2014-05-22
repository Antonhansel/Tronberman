/*
** Saving.cpp for saving in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  21 01:14:50 2014 Antonin Ribeaud
** Last update Wed May  21 01:14:50 2014 Antonin Ribeaud
*/

#include "Saving.hpp"

Saving::Saving(std::vector<std::string> &fileName)
{
  _isGood = true;
  while (!fileName.empty())
  {
    bool  error;

    _nbrLine = 0;
    _name = fileName.back();
    error = true;
    error = loadMap(fileName.back());
    if (error == false)
      std::cout << "Failed to Load the map: \"" << fileName.back() << "\"." << std::endl;
    else
      addListMap();
    fileName.pop_back();
  }
  if (_listMap.size() == 0)
    _isGood = false;
}

Saving::Saving(std::string &fileName, Core *core) : _name(fileName)
{
  Map *m = core->getMap();
  _map = m->getMap();
  _player = core->getPlayer();
  _spawn = m->getSpawn();
  _sizeMap = m->getSize();
  _nbrPlayer = 0;
  _nbrBot = 0;
  _file.open(fileName.c_str());
  if (!_file.is_open())
    std::cout << "Error opening." << std::endl; 
  else
  {
    if (saveMap() == false)
      std::cout << "Error saving" << std::endl;
    _file.close();
  }
}

Saving::Saving(std::string &fileName, AObject **objects, int size)
{
  _name = fileName;
  _map = objects;
  _sizeMap = size;
  _nbrPlayer = 0;
  _nbrBot = 0;
  _file.open(fileName.c_str());
  if (!_file.is_open())
    std::cout << "Error opening." << std::endl; 
  else
  {
    if (saveMap() == false)
      std::cout << "Error saving" << std::endl;
    _file.close();
  }
}

Saving::~Saving()
{
	delete _map;
	while (_spawn.size() > 0)
		_spawn.pop_back();
}

bool    Saving::loadSize(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<size>";
  std::string       out = "</size>";

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 1)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  _sizeMap = tab.back();
  _map = new AObject *[_sizeMap * _sizeMap];
  memset(_map, 0, (_sizeMap * _sizeMap) * sizeof(AObject *));
  return true;
}

bool    Saving::loadCase(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<case>";
  std::string       out = "</case>";
  AObject           *tmp;
  std::pair<float, float> pos;
  type _type;
  int x;
  int y;
  int t;

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 3)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  t = tab.back();
  tab.pop_back();
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  _type = (type)t;
  tmp = create<Cube>();
  pos = std::make_pair(x, y);
  tmp->setType(_type);
  tmp->setPos(pos);
  tmp->initialize();
  _map[x * _sizeMap + y] = tmp;
  return true;
}

bool    Saving::loadSpawn(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<spawn>";
  std::string       out = "</spawn>";
  int x;
  int y;

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 2)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  tab.pop_back();
  _spawn.push_back(std::make_pair(x, y));
  return true;
}

bool    Saving::loadMap(std::string &file_name)
{
  std::list<std::string>  file;
  std::string             str;
  std::ifstream           infile(file_name.c_str());
  std::size_t             pos;
  bool                    error;

  while (std::getline(infile, str))
    file.push_back(str);
  if (file.size() > 2)
  {
    while ((pos = file.front().find("<map>")) == std::string::npos
          && file.size() > 0)
    {
      file.pop_front();
      _nbrLine++;
    }
    _nbrLine++;
    file.pop_front();
    std::string front;
    while ((pos = file.front().find("</map")) == std::string::npos
          && file.size() > 0)
    {
      error = true;
      front = file.front();
      if ((pos = front.find("<size>")) != std::string::npos)
        error = loadSize(file);
      if ((pos = front.find("<case>")) != std::string::npos)
        error = loadCase(file);
      if ((pos = front.find("<spawn>")) != std::string::npos)
        error = loadSpawn(file);
      if (error == false)
        return false;
      if (file.front() == "")
      {
        file.pop_front();
        _nbrLine++;
      }
    }
    if (_sizeMap == 0)
      return false;
  }
  else
  {
    std::cout << "The map is not found." << std::endl;    
    return false;
  }
  return true;
}

void        Saving::myParseur(std::vector<int> &tab, std::string &str)
{
  std::size_t   x;
  std::size_t   y;
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
    ++y;
  }
  std::istringstream buffer(str.substr(x, y - x + 1));
  buffer >> v;
  tab.push_back(v);
}

bool        Saving::myBalise(std::string &in, std::string &out, 
                              std::string &str, std::string &front)
{
  std::size_t pos = str.find(in) + in.length();
  std::size_t pos2 = str.find(out);

  if (pos2 != std::string::npos)
    str = str.substr(pos, pos2 - pos);
  else
  {
    std::cout << "Error line " << _nbrLine <<
    " in the file \"" << _name << "\"" << std::endl;
    return (false);
  }
  front = front.substr(pos2 + out.length());
  return (true);
}

bool    Saving::savePlayer()
{
  for (int i = 1; i <= _nbrPlayer; i++)
  {
    _file << "<player>" << std::endl;
    _file << "<id>" << _player[i]->getId() << "</id>" << std::endl;
    _file << "<life>" << _player[i]->getLife() << "</life>" << std::endl;
    _file << "<range>" << _player[i]->getRange() << "</range>" << std::endl;
    _file << "<stock>" << _player[i]->getStock() << "</stock>" << std::endl;
    _file << "<shield>" << _player[i]->getShield() << "</shield>" << std::endl;
    _file << "</player>" << std::endl;
  }
  return (true);
}

bool    Saving::saveSpawn()
{
  std::vector<std::pair<int, int> >    obj;

  obj = _spawn;
  while (!obj.empty())
  {
    std::pair<int, int> pos = obj.front();
    _file << "<spawn>" << pos.second << " " << pos.first << "</spawn>" << std::endl;
    obj.pop_back();
  }
  return true;
}

bool    Saving::saveMap()
{
  _file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
  _file << "<map>" << std::endl;
  _file << "<size>" << _sizeMap << "</size>" << std::endl;
  for (int y = 0; y < _sizeMap; y++)
    {
      for (int x = 0; x < _sizeMap; x++)
      {
        if (_map[x + _sizeMap * y] != NULL)
        {
          type t = _map[x + _sizeMap * y]->getType();
          if (t != BOMB && t != BONUS && t != LASER)
          {
            _file << "<case>" << y << " " << x << " " << 
            _map[x + _sizeMap * y]->getType() << "</case>"<< std::endl;
        }
      }
    }
  }
  saveSpawn();
  _file << "</map>" << std::endl;
  return true;
}

std::vector<Map *>                      Saving::getListMap()
{
  return _listMap;
}

void                                    Saving::addListMap()
{
  Map *myMap = new Map(_sizeMap);

  myMap->setMap(_map);
  myMap->setSpawn(_spawn);
  myMap->setSize(_sizeMap);
  std::cout << "Map \"" << _name << "\" load correctly." << std::endl;
  _listMap.push_back(myMap);
}
