#ifndef _MAP_FILLER_
# define _MAP_FILLER_

#include "Map.hpp"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class MapFiller
{
public:
	MapFiller(Map *);
	~MapFiller();
	void 	fillMap(gdl::Clock &);
	void 	moveMatrice();
	void 	moveCube();
	//void 	genMatrice();
private:
	// int initial_direction;
	// int n;
	// int p;
 // 	int row_right;
 // 	int column_down;
 // 	int row_left;
 // 	int column_up;
	// int 	r;
	// int 	c;
	int 	_count;
	Map 	*_map;
	double _time;
	int 	_size;
	AObject	*_cursor;
};

#endif /*_MAP_FILLER_*/