/*
** Hub.hpp for Text in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:24 2014 Antonin Ribeaud
// Last update Wed May 14 01:48:25 2014 Mehdi Chouag
*/

#include <sstream>
#include "Text.hpp"
#include "Player.hpp"

enum Display 
{
	NBLIFE = 0,
	NBRANGE = 1,
	NBBOMB = 2,
	TIMER = 3
};

class Hud : public Text
{
public:
	Hud(Camera *, Loader *);
	~Hud();
	void 	init(Player *);
	void	update(Player *);
	void	updateFPS(int);
	void	draw(Player *);
	void	drawFPS() const;
	void 	setScreen(int);
	bool	setClock(gdl::Clock &);
	void	resetClock();
private:
	std::string convertToString(int, const std::string);
	void 		delGeometry(std::vector<Geometry *> &);
	void		drawPlayer1();
	void		drawPlayer2();
	void		updatePlayer1(Player *);
	void		updatePlayer2(Player *);
	void		updateRep();
	void		drawTimer();

private:
	int 	_screen;
	int 	bombPlayer1;
	int 	rangePlayer1;
	int 	lifePlayer1;
	int 	bombPlayer2;
	int 	rangePlayer2;
	int 	lifePlayer2;
	int 	_row2;
	int 	_row1;
	int 	_col1;
	int 	_fps;
	float	_timer;
	bool	_timerDouble;
	glm::mat4 _transformation;
	std::map<int, void(Hud::*)(Player *) > _updatePlayer;
	std::map<int, void(Hud::*)() > _drawPlayer;
	std::map<Display, std::vector<gdl::Geometry *> > _player1;
	std::map<Display, std::vector<gdl::Geometry *> > _player2;
	std::vector<gdl::Geometry *>	_time;
	std::vector<gdl::Geometry *> _affFPS;
};