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

Map::Map(int size) : _name(PATH)
{
    genereteName();
    _size_x = size;
    _size_y = size;
    std::cout << "SIZE" << size << std::endl;
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

void    Map::genereteName()
{
  std::string acceptes="abcdefghijklmnopqrstuvwyz";
  acceptes+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 10; i++)
  {
    size_t pos = rand()%52;

    _name +=acceptes[pos];
  }
  _name += ".xml";
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

bool    Map::check_pos(int x, int y)
{
    std::vector<std::pair<int, int> >::iterator it;

    for (it = _spawns.begin(); it < _spawns.end(); ++it)
        if (x == (*it).first && y == (*it).second)
            return true;
    return false;
}

std::vector<std::pair<int, int> >   &Map::setSpawn(int nb)
{
    int   x;
    int   y;

    srand(time(NULL));
    x = 0;
    y = 0;
    for (int i = 0; i < nb; i++)
    {
        while ((x == 0 && y == 0) || check_pos(x, y))
        {
            x = rand() % (_size_x - 2) + 1;
            y = rand() % (_size_y - 2) + 1;
            if (x % 2 == 0)
                x--;
            if (y % 2 == 0)
                y--;
        }
        _spawns.push_back(std::make_pair(x, y));
        _deleteSide(x, y);
    }
    return (_spawns);
}

int     Map::getSize() const
{
    return (_size_x);
}

void     Map::setSize(int sizeX)
{
    _size_x = sizeX;
    _size_y = sizeX;
}

void    Map::setMap(AObject **map)
{
    _map = map;
}

void    Map::setSpawn(std::vector<std::pair<int, int> > &spawns)
{
    _spawns = spawns;
}

AObject **Map::getMap() const
{
    return _map;
}

std::vector<std::pair<int, int> > Map::getSpawn() const
{
    return _spawns;
}

std::string     Map::getName() const
{
  return _name;
}