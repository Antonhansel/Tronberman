/*
** Hud.cpp for Hub in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:24 2014 Antonin Ribeaud
// Last update Wed May 14 01:48:25 2014 Mehdi Chouag
*/

#include "Hud.hpp"

Hud::Hud(Camera *cam, Loader *loader) :
	Text(cam, loader)
{
	_drawPlayer[1] = &Hud::drawPlayer1;
	_drawPlayer[2] = &Hud::drawPlayer2;
	_updatePlayer[1] = &Hud::updatePlayer1;
	_updatePlayer[2] = &Hud::updatePlayer2;
	bombPlayer1 = 0;
	bombPlayer2 = 0;
	rangePlayer1 = 0;
	rangePlayer2 = 0;
	lifePlayer1 = 0;
	lifePlayer2 = 0;
	_col1 = 0;
	_fps = 0;
	_timer = 120;
	_timerDouble = false;
}

void	Hud::setScreen(int screen)
{
	if (screen == 1)
	{
		_col1 = 1600;
		_timerDouble = true;
	}
	else
		_timerDouble = false;
}

void	Hud::update(Player *cur)
{
	(this->*_updatePlayer[cur->getId()])(cur);
}

void	Hud::updatePlayer1(Player *cur)
{
	int	minuts = 0;
	int	seconds = 0;

	seconds = ((int)(_timer)) % 60;
	minuts = _timer / 60;
	if (cur->getStock() != bombPlayer1)
	{
		bombPlayer1  = cur->getStock();	
		delGeometry(_player1[NBBOMB]);
		_player1[NBBOMB] = this->putstr(convertToString(bombPlayer1, "Bombs").c_str(), 32, true);
	}
	if (cur->getRange() != rangePlayer1)
	{
		rangePlayer1  = cur->getRange();
		delGeometry(_player1[NBRANGE]);
		_player1[NBRANGE] = this->putstr(convertToString(rangePlayer1, "Range").c_str(), 32, true);
	}
	if (cur->getLife() != lifePlayer1)
	{
		lifePlayer1  = cur->getLife() + 1;
		delGeometry(_player1[NBLIFE]);
		_player1[NBLIFE] = this->putstr(convertToString(lifePlayer1, "Life ").c_str(), 32, true);
	}
	if (_timerDouble == true)
	{
		if (_timer > 0)
		{
			delGeometry(_player1[TIMER]);
			_player1[TIMER] = this->putstr((convertToString(minuts, " : ") + convertToString(seconds, "")).c_str(), 32, false);
		}
	}
	else
	{	
		if (_timer > 0)
		{
			delGeometry(_time);
			_time = this->putstr((convertToString(minuts, " : ") + convertToString(seconds, "")).c_str(), 64, false);
		}
	}
}

void	Hud::updatePlayer2(Player *cur)
{
	int	minuts = 0;
	int	seconds = 0;

	seconds = ((int)(_timer)) % 60;
	minuts = _timer / 60;
	if (cur->getStock() != bombPlayer2)
	{
		bombPlayer2  = cur->getStock();	
		delGeometry(_player2[NBBOMB]);
		_player2[NBBOMB] = this->putstr(convertToString(bombPlayer2, "Bombs").c_str(), 32, true);
	}
	if (cur->getRange() != rangePlayer2)
	{
		rangePlayer2  = cur->getRange();
		delGeometry(_player2[NBRANGE]);
		_player2[NBRANGE] = this->putstr(convertToString(rangePlayer2, "Range").c_str(), 32, true);
	}
	if (cur->getLife() != lifePlayer2)
	{
		lifePlayer2  = cur->getLife() + 1;
		delGeometry(_player2[NBLIFE]);
		_player2[NBLIFE] = this->putstr(convertToString(lifePlayer2, "Life ").c_str(), 32, true);
	}
	if (_timerDouble == true)
	{
		
		if (_timer > 0)
		{
			delGeometry(_player2[TIMER]);
			_player2[TIMER] = this->putstr((convertToString(minuts, " : ") + convertToString(seconds, "")).c_str(), 32, false);
		}
	}
}

void	Hud::updateFPS(int fps)
{
	if (_fps != fps)
	{
		_fps = fps;
		delGeometry(_affFPS);
		_affFPS = this->putstr(convertToString(_fps, "FPS").c_str(), 64, true); 
	}
}

void	Hud::draw(Player *cur)
{
	updateRep();
	_loader->bindTexture(SELECTED);
  	_camera->setMode();
  	(this->*_drawPlayer[cur->getId()])();
  	if (_timerDouble == false && _timer > 0)
  		drawTimer();
  	_camera->setMode();
}

void	Hud::drawTimer()
{
	int	col;

	col = 650;
	for (std::vector<Geometry *>::iterator it = _time.begin(); it != _time.end(); ++it)
	{
		_transformation = glm::translate(glm::mat4(1), glm::vec3(col, 0, 0));
		(*it)->draw(_camera->getShader(), _transformation, GL_QUADS);
		col += 40;
	}
}

void	Hud::drawPlayer1()
{
	std::map<Display, std::vector<gdl::Geometry *> >::const_iterator it;
	int col;
	int row;

	col = _col1;
	row = 0;
	for (it = _player1.begin(); it != _player1.end(); ++it)
    {
      for (size_t i(0); i != (*it).second.size(); i++)
      {
        _transformation = glm::translate(glm::mat4(1), glm::vec3(col, row, 0));
        (*it).second[i]->draw(_camera->getShader(), _transformation, GL_QUADS);
        col += 20;
      }
      col = _col1;
      row += 32;
  	}	
}

void	Hud::drawPlayer2()
{
	std::map<Display, std::vector<gdl::Geometry *> >::const_iterator it;
	int col;
	int row;

	col = 0;
	row = 0;
	for (it = _player2.begin(); it != _player2.end(); ++it)
    {
      for (size_t i(0); i != (*it).second.size(); i++)
      {
        _transformation = glm::translate(glm::mat4(1), glm::vec3(col, row, 0));
        (*it).second[i]->draw(_camera->getShader(), _transformation, GL_QUADS);
        col += 20;
      }
      col = 0;
      row += 32;
  	}
}

void		Hud::drawFPS() const
{
	int col;
	glm::mat4 transformation;

	col = 0;
	_loader->bindTexture(SELECTED);
	_camera->setMode();
    for (size_t i(0); i != _affFPS.size(); i++)
      {
        transformation = glm::translate(glm::mat4(1), glm::vec3(col, 940, 0));
        _affFPS[i]->draw(_camera->getShader(), transformation, GL_QUADS);
        col += 50;
      }
    _camera->setMode();
}

std::string Hud::convertToString(int value, const std::string text)
{
	std::stringstream ss;

  	ss << value;
  	return (text + " " + ss.str());
}

Hud::~Hud()
{
	std::map<Display, std::vector<gdl::Geometry *> >::iterator it;

	for (it = _player1.begin(); it != _player1.end(); ++it)
		delGeometry((*it).second);
	for (it = _player2.begin(); it != _player2.end(); ++it)
		delGeometry((*it).second);
	delGeometry(_affFPS);
}

void	Hud::delGeometry(std::vector<Geometry *> &v)
{
	for (size_t i(0); i != v.size(); i++)
		delete v[i];
}

void	Hud::updateRep()
{
	if (_camera->isSplit())
		_col1 = 700;
	else
		_col1 = 1600;
}

bool 	Hud::setClock(gdl::Clock &c)
{
	if (_timer > 0)
	{
		_timer -= c.getElapsed();
		return (false);		
	}
	_timer = -1;
	return (true);
}

void	Hud::resetClock()
{
	_timer = 120;
}