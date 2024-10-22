/*
** Hud.cpp for Hub in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:24 2014 Antonin Ribeaud
// Last update Mon Jun 23 17:45:52 2014 Mehdi Chouag
*/

#include "Hud.hpp"

Hud::Hud(Camera *cam, Loader *loader) :
	Text(cam, loader)
{
	_saving = false;
	_save = this->putstr("SAVING...", 50, false);
	_drawPlayer[1] = &Hud::drawPlayer1;
	_drawPlayer[2] = &Hud::drawPlayer2;
	_updatePlayer[1] = &Hud::updatePlayer1;
	_updatePlayer[2] = &Hud::updatePlayer2;
	_death[VICTORY] = this->putstr("YOU WIN", 100, true);
	_death[FATALITY] = this->putstr("FATALITY", 100, true);
	_pauseText = this->putstr("PAUSE", 50, false);
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
	_pause = false;
}

void	Hud::setScreen(const int screen)
{
	(screen == 1) ? (_timerDouble = true) : (_timerDouble = false);
}

void	Hud::update(const Player *cur)
{
	(this->*_updatePlayer[cur->getId()])(cur);
}

void	Hud::updatePlayer1(const Player *cur)
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
			_player1[TIMER] = this->putstr((convertToStringN(minuts, ":") + convertToStringN(seconds, "")).c_str(), 32, false);
		}
	}
	else
	{	
		if (_timer > 0)
		{
			delGeometry(_time);
			_time = this->putstr((convertToStringN(minuts, ":") + convertToStringN(seconds, "")).c_str(), 64, false);
		}
	}
}

void	Hud::updatePlayer2(const Player *cur)
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
			_player2[TIMER] = this->putstr((convertToStringN(minuts, ":") + convertToStringN(seconds, "")).c_str(), 32, false);
		}
	}
}

void 	Hud::setPause(const bool status)
{
	_pause = status;
}

void	Hud::updateFPS(const int fps)
{
	if (_fps != fps)
	{
		_fps = fps;
		delGeometry(_affFPS);
		_affFPS = this->putstr(convertToString(_fps, "FPS").c_str(), 64, true); 
	}
}

void	Hud::draw(const Player *cur)
{
	updateRep();
	_loader->bindTexture(SELECTED);
  	_camera->setMode();
  	(this->*_drawPlayer[cur->getId()])();
  	if (_timerDouble == false && _timer > 0)
  		drawTimer();
  	if (_saving)
  		drawSaving();
  	if (_pause)
  		drawPause();
  	_camera->setMode();
}

void	Hud::drawTimer()
{
	int	col;

	col = 800;
	for (std::vector<Geometry *>::const_iterator it = _time.begin(); it != _time.end(); ++it)
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
        col += 28;
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
        col += 28;
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

Hud::~Hud()
{
	std::map<Display, std::vector<gdl::Geometry *> >::iterator it;
	std::map<Death, std::vector<gdl::Geometry *> >::iterator it2;

	for (it = _player1.begin(); it != _player1.end(); ++it)
		delGeometry((*it).second);
	for (it = _player2.begin(); it != _player2.end(); ++it)
		delGeometry((*it).second);
	for (it2 = _death.begin(); it2 != _death.end(); ++it2)
		delGeometry((*it2).second);
	delGeometry(_affFPS);
}

void	Hud::delGeometry(std::vector<Geometry *> const &v)
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

bool 	Hud::setClock(gdl::Clock const &c)
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

float 	Hud::getTimer() const
{
	return (_timer);
}

void	Hud::setTimer(const float timer)
{
	_timer = timer;
}

void	Hud::drawSaving()
{
	int	col;

	col = (_camera->isSplit()) ? 400 : 800;
	for (std::vector<Geometry *>::const_iterator it = _save.begin(); it != _save.end(); ++it)
	{
		_transformation = glm::translate(glm::mat4(1), glm::vec3(col, 300, 0));
		(*it)->draw(_camera->getShader(), _transformation, GL_QUADS);
		col += 40;
	}
}

void 	Hud::drawPause()
{
	int	col;

        col = (_camera->isSplit()) ? 400 : 800;
	for (std::vector<Geometry *>::const_iterator it = _pauseText.begin(); it != _pauseText.end(); ++it)
	{
		_transformation = glm::translate(glm::mat4(1), glm::vec3(col, 300, 0));
		(*it)->draw(_camera->getShader(), _transformation, GL_QUADS);
		col += 40;
	}
}

void	Hud::drawDeath(const Death type)
{
	int	col;
	col = 550;

	_camera->setMode();
	for (std::vector<Geometry *>::const_iterator it = _death[type].begin(); it != _death[type].end(); ++it)
	{
		_transformation = glm::translate(glm::mat4(1), glm::vec3(col, 300, 0));
		(*it)->draw(_camera->getShader(), _transformation, GL_QUADS);
		col += 80;
	}
	_camera->setMode();
}

std::string Hud::convertToString(const int value, const std::string &text)
{
	std::stringstream ss;

  	ss << value;
  	return (text + " " + ss.str());
}

std::string Hud::convertToStringN(const int value, const std::string &text)
{
	std::stringstream ss;

  	ss << value;
  	return (ss.str() + text);
}

void	Hud::displaySaving(const bool b)
{
	_saving = b;
}
