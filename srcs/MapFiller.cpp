#include "MapFiller.hpp"

MapFiller::MapFiller(Map *map, Loader *loader, std::vector<Player*> *player)
{
	_map = map;
	_loader = loader;
	_time = 0;
	_size = _map->getSize();
	row_right = 1; 
	n = _size;
	column_down = n-2;
	row_left = n-2; 
	column_up = 1;
	initial_direction = UP;
	p = 1;
	c = 1;
	r = 1;
	_move = false;
	_player = player;
	_cursor = create<Cube>();
    _cursor->setType(BORDER);
    _cursor->translate(glm::vec3(_size/2, 1, _size/2));
    moveCube();
    _cursor->initialize();
}

void MapFiller::moveCube()
{
	std::pair<float, float> pos;
	pos = std::make_pair(r, c);
	_cursor->setAbsPos(pos);
	_cursor->translate(glm::vec3(0, 1, 0));
}

MapFiller::~MapFiller()
{}

void MapFiller::draw(gdl::AShader &shader)
{
	_loader->bindTexture(BLOCK);
	_loader->drawGeometry(shader, _cursor->getTransformation());
}

void MapFiller::checkPlayers()
{
	std::vector<Player*>::iterator it;
	std::pair<float, float> pos;

	pos = _cursor->getPos();
	for (it = _player->begin(); it != _player->end(); ++it)
	{
		if ((*it)->realPos((*it)->getPos()) == pos)
			(*it)->setIsAlive();
	}
}

void MapFiller::fillMap(gdl::Clock &clock)
{
	_time += clock.getElapsed();
	if (_time > 0.0001)
	{ 
		if (_move == false)
		{
			changePos();
			moveCube();
			_time = 0;
			_move = true;
		}
		else if (_move == true)
		{
			_move = false;
			if (!_map->getCase(_cursor->getPos().first, _cursor->getPos().second))
			{
				//_map->deleteCube(_cursor->getPos().first, _cursor->getPos().second);
				_map->addCube(_cursor->getPos().first, _cursor->getPos().second, BORDER);
				checkPlayers();
			}
		}
		_time = 0;
	}
}

std::pair<float, float> MapFiller::changePos()
{
	std::pair<float, float> pos;
	if(initial_direction == UP)
	{
	  if (c == 0)
	  	r = row_right++;
	  if (c < n)
         c++;
      else
      	{
      	 r = 0;
	  	 initial_direction = RIGHT;
	  	}
	}
    else if (initial_direction == RIGHT)
	{
	  if (r == 0)
	  	c = column_down--;
	  if (r < n)
        r++;
       else
       {
       	c = n - 1;
	  	initial_direction = DOWN;
	   }
	}
    else if (initial_direction == DOWN)
	{
	  if (c == n -1)
	   r = row_left-- ;
	  if (c >= 0)
        c--;
      else
       {
       	r = n - 1;
	  	initial_direction = LEFT;
	   }
	}
    else
	{
	  if (r == n - 1)
	  	c = column_up++;
	  if (r >= 0)
        r--;
      else
       {
      	c = 0;
	  	initial_direction = UP;
	   }
	}
  return (pos);
}
