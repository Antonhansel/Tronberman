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
//#include "Player.hpp"

Saving::Saving(std::vector<std::string> &fileName)
{
  _isGood = true;
  while (!fileName.empty())
  {
    bool  error;

    _nbrLine = 0;
    _name = fileName.back();
    _sizeMap = 0;
    error = true;
    error = loadMap(fileName.back());
    _nbrLine = 0;
    error = loadPlayer(fileName.back());
    if (error == false)
      std::cout << "Failed to Load the map: \"" << fileName.back() << "\"." << std::endl;
    else
    {
      addListMap();
      addListPlayer();
    }
    fileName.pop_back();
  }
  if (_listMap.size() == 0)
    _isGood = false;
}

Saving::Saving(std::string fileName, Core *core) : _name(fileName)
{
  Map *m = core->getMap();
  _map = m->getMap();
  _player = core->getPlayer();
  _spawn = m->getSpawn();
  _sizeMap = m->getSize();
  _nbrPlayer = core->getNbrPlayer();
  _nbrBot = _player.size() - _nbrPlayer;
  _file.open(_name.c_str());
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
  while (_player.size() > 0)
    _player.erase(_player.begin());
  while (!_spawn.empty())
    _spawn.pop_back();
  while (!_listMap.empty())
    _listMap.pop_back();
  while (!_players .empty())
     _players.pop_back();
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

bool    Saving::loadName(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<name>";
  std::string       out = "</name>";

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  std::cout << "load map " << str << std::endl;
  if (str == "")
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  _name = str;
  return true;
}

bool    Saving::loadRange(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<range>";
  std::string       out = "</range>";

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
  player->setRange(tab.back());
  return true;
}

bool    Saving::loadStock(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<stock>";
  std::string       out = "</stock>";

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
  player->setStock(tab.back());
  return true;
}

bool    Saving::loadId(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<id>";
  std::string       out = "</id>";

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
  player->setId(tab.back());
  return true;
}

bool    Saving::loadLife(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<life>";
  std::string       out = "</life>";

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
  player->setLife(tab.back());
  return true;
}

bool    Saving::loadType(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<type>";
  std::string       out = "</type>";

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
  player->setType((type)(tab.back()));
  return true;
}
bool    Saving::loadPos(std::list<std::string> &file, Player *player)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<pos>";
  std::string       out = "</pos>";

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
  std::pair<float, float> pos;
  pos.first = tab.back();
  tab.pop_back();
  pos.second = tab.back();
  std::cout << pos.first << " " << pos.second << std::endl;
  player->setPos(pos);
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

  if (_sizeMap == 0)
    return false;
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

  if (_sizeMap == 0)
    return false;
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
  size_t                  pos = 0;
  bool                    error;

  while (std::getline(infile, str))
    file.push_back(str);
  while (!file.empty() && (pos = file.front().find("<map>")) == std::string::npos)
  {
    file.pop_front();
   _nbrLine++;
  }
  if (!file.empty())
  {
    _nbrLine++;
    file.pop_front();
  }
  std::string front;
  while (!file.empty() && (pos = file.front().find("</map")) == std::string::npos)
  {
    error = true;
    front = file.front();
    ((pos = front.find("<name>")) != std::string::npos) ? (error = loadName(file)) : 0;
    ((pos = front.find("<size>")) != std::string::npos) ? (error = loadSize(file)) : 0;
    ((pos = front.find("<case>")) != std::string::npos) ? (error = loadCase(file)) : 0;
    ((pos = front.find("<spawn>")) != std::string::npos) ? (error = loadSpawn(file)) : 0;
    if (error == false)
      return false;
    file.pop_front();
    if (file.empty())
      return false;
    _nbrLine++;
  }
  return true;
}

bool    Saving::loadPlayer(std::string &file_name)
{
  std::list<std::string>  file;
  std::string             str;
  std::string             front;
  std::ifstream           infile(file_name.c_str());
  size_t                  pos = 0;
  bool                    error;
  Player *player;

  while (std::getline(infile, str))
    file.push_back(str);
  while (!file.empty())
  {
    if (!file.empty() && (pos = file.front().find("<player>")) != std::string::npos)
    {
      player = new Player();
      while (!file.empty() && (pos = file.front().find("</player>")) == std::string::npos)
      {
        error = true;
        front = file.front();
        ((pos = front.find("<id>")) != std::string::npos) ? (error = loadId(file, player)) : 0;
        ((pos = front.find("<type>")) != std::string::npos) ? (error = loadType(file, player)) : 0;
        ((pos = front.find("<life>")) != std::string::npos) ? (error = loadLife(file, player)) : 0;
        ((pos = front.find("<range>")) != std::string::npos) ? (error = loadRange(file, player)) : 0;
        ((pos = front.find("<pos>")) != std::string::npos) ? (error = loadPos(file, player)) : 0;
        ((pos = front.find("<stock>")) != std::string::npos) ? (error = loadStock(file, player)) : 0;
        file.pop_front();
        if (file.empty() || error == false)
          return false;
        _nbrLine++;
      }
      _player[player->getId()] = player;
    }
    else
    {
      _nbrLine++;
      file.pop_front();
    }
  }
  return (true);
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
  std::pair<float, float> pos;

  for (int i = 1; i <= _nbrPlayer; i++)
  {
    pos = _player[i]->getPos();
    _file << "<player>" << std::endl;
    _file << "<id>" << _player[i]->getId() << "</id>" << std::endl;
    _file << "<type>" << PLAYER << "</type>" << std::endl;
    _file << "<life>" << _player[i]->getLife() << "</life>" << std::endl;
    _file << "<range>" << _player[i]->getRange() << "</range>" << std::endl;
    _file << "<stock>" << _player[i]->getStock() << "</stock>" << std::endl;
    _file << "<pos>" << pos.second << " " << pos.first << "</pos>" << std::endl;
    _file << "</player>" << std::endl;
  }
  for (int i = 3; i <= (_nbrBot + 2); i++)
  {
    pos = _player[i]->getPos();
    _file << "<player>" << std::endl;
    _file << "<id>" << _player[i]->getId() << "</id>" << std::endl;
    _file << "<type>" << BOT << "</type>" << std::endl;
    _file << "<life>" << _player[i]->getLife() << "</life>" << std::endl;
    _file << "<range>" << _player[i]->getRange() << "</range>" << std::endl;
    _file << "<stock>" << _player[i]->getStock() << "</stock>" << std::endl;
    _file << "<pos>" << pos.second << " " << pos.first << "</pos>" << std::endl;
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
    _file << "<spawn>" << pos.first << " " << pos.second << "</spawn>" << std::endl;
    obj.pop_back();
  }
  return true;
}

bool    Saving::saveMap()
{
  _file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
  _file << "<map>" << std::endl;
  _file << "<name>" << _name << "</name>" << std::endl;
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
            _file << "<case>" << x << " " << y << " " << 
            _map[x + _sizeMap * y]->getType() << "</case>"<< std::endl;
        }
      }
    }
  }
  _file << "</map>" << std::endl;
  savePlayer();
  return true;
}

std::vector<Map *>                      Saving::getListMap()
{
  return (_listMap);
}

std::vector<Map *>                      Saving::getCostumListMap()
{
  while (_listMap.empty() || _listMap.size() < 5)
  {
    _listMap.push_back(new Map((rand() % 20) + 10));
  }
  return (_listMap);
}

std::vector< std::map<int, Player *> >  Saving::getListPlayer()
{
  return (_players);
}

void                                    Saving::addListPlayer()
{
  _players.push_back(_player);
}

void                                    Saving::addListMap()
{
  Map *myMap = NULL;

  if (_sizeMap >= 10)
    myMap = new Map(_sizeMap);
  if (myMap != NULL && _map != NULL)
    myMap->setMap(_map);
  if (myMap != NULL && !_spawn.empty())
    myMap->setSpawn(_spawn);
  if (myMap != NULL)
    _listMap.push_back(myMap);
}