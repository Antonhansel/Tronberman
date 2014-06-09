#ifndef _MAP_FILLER_
# define _MAP_FILLER_

# include "Map.hpp"
# include "Loader.hpp"
# include "Player.hpp"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class MapFiller
{
public:
	MapFiller(Map *, Loader *, std::vector<Player*> *player);
	~MapFiller();
	void 	fillMap(gdl::Clock &);
	void 	moveMatrice();
	void 	moveCube();
	void 	draw(gdl::AShader &shader);
	void 	checkPlayers() const;
	std::pair<float, float> 	changePos();
private:
	int 	initial_direction;
	int 	n;
	int 	p;
 	int 	row_right;
 	int 	column_down;
 	int 	row_left;
 	int 	column_up;
	int 	r;
	int 	c;
private:
	std::vector<Player *> *_player;
	bool 	_move;
	int 	_count;
	Map 	*_map;
	AObject	*_cursor;
	Loader	*_loader;
	double 	_time;
	int 	_size;
};

#endif /*_MAP_FILLER_*/