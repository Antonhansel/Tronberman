#include "MapFiller.hpp"

MapFiller::MapFiller(Map *map)
{
	_map = map;
	_time = 0;
	_size = _map->getSize();
	// row_right = 0; 
	// column_down = n-1;
	// row_left = n-1; 
	// column_up = 0;
	// initial_direction = UP;
	// n = _size;
	// p = 1;
	// c = 0;
	// r = 0;
	_count = _size * _size;
	_cursor = new Cube();
	_cursor = create<Cube>();
    _cursor->setType(BLOCK);
    _cursor->translate(glm::vec3(0, 1, 0));
    moveCube();
    _cursor->initialize();
	//genMatrice();
}

void MapFiller::moveCube()
{
	std::pair<float, float> pos; 
	pos = std::make_pair(0, 0);
	_cursor->setPos(pos);
}

MapFiller::~MapFiller()
{

}

void MapFiller::fillMap(gdl::Clock &clock)
{
	_time += clock.getElapsed();
	if (_time <= 1)
	{
		moveCube();
		//la on va spawn un bloc
	}
	else if (_time > 2 && _time < 3)
	{
		//la on va descendre le bloc
	}
	if (_time >= 3)
	 _time = 0;
}

// void MapFiller::genMatrice()
// {
//   while(p != n*n+1)
//   {
//     if(initial_direction == UP)
// 	{
// 	  r = row_right++;
// 	  if (c < n)
//         {
//          c++;
//         }
//       else
//       	{
// 	  	 initial_direction = RIGHT;
// 	  	}
// 	}
//     else if(initial_direction == RIGHT)
// 	{
// 	  c = column_down--; 
// 	  for(r = 0 ; r < n ; r++)
//         {
//         }
// 	  initial_direction = DOWN ;
// 	}
//     else if(initial_direction == DOWN)
// 	{
// 	  r = row_left-- ;
// 	  for(c = n-1 ; c >= 0 ; c--)
//         {
//         }
// 	  initial_direction = LEFT ;
// 	}
//     else if(initial_direction == LEFT)
// 	{
// 	  c = column_up++;
// 	  for(r = n-1 ; r >= 0 ; r--)
//         {
//         }
// 	  initial_direction = UP ;
// 	}
//   }
// }
