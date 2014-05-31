#include "Saving.hpp"

Saving::Saving(const std::string &fileName) :
	_fileName(fileName)
{
	if ((_fileName.substr(_fileName.size() - 4, 4)).compare(".xml") == 0)
		_extension = true;
	else
		_extension = false;
	_map = NULL;
	_timer = 0;
	_playerNb = 1;
}

Saving::~Saving()
{

}

std::string 	Saving::calcCheckSum(std::string s)
{
	return (md5(s));
}

bool	Saving::saveMap(const Map *m)
{
	AObject *ao;
	int	size;

	size = m->getSize();
	if (m != NULL)
	{
		_file << "<map>" << std::endl;
		_file << "<size>" << m->getSize() << "</size>" << std::endl;
		for (int y = 1; y < size - 1; y++)
		{
			for (int x = 1; x < size - 1; x++)
			{
				ao = m->getCase(x, y);
				if (ao != NULL)
				{
					if (ao->getType() != BOMB && ao->getType() != BONUS && ao->getType() != LASER)
						_file << "<case><x>" << x << "</x><y>" << y << "</y><type>" <<  ao->getType() << "</type></case>" << std::endl;
				}
			}
		}
		_file << "</map>" << std::endl;
		return (true);
	}
	return (false);
}

bool	Saving::savePlayer(const Player *p)
{
	if (p != NULL)
	{
		std::pair<float, float>	pp;
		pp = p->getPos();
		_file << "<player><id>" << p->getId() << "</id><posx>" << pp.first << "</posx><posy>" << pp.second << "</posy><shield>" << p->getShield() << "</shield><stock>" << p->getStock() << "</stock><life>" << p->getLife() << "</life><range>" << p->getRange() << "</range><speed>" << p->getSpeed() << "</speed><score>" << p->getScore() << "</score></player>" << std::endl;
		return (true);
	}
	return (false);
}

bool	Saving::saveAllPlayer(const std::vector<Player *> &p)
{
	for (std::vector<Player *>::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		if (!savePlayer(*it))
			return (false);
	}
	return (true);
}

bool	Saving::saveTimer(double t)
{
	_file << "<timer>" << t << "</timer>" << std::endl;
	return (true);
}

bool	Saving::saveCheckSum()
{
	std::ostringstream	out;
	std::string 		s("");

	_fileIn.open(_fileName.c_str(), std::ifstream::in);
	if (_fileIn.is_open())
	{
		out << _fileIn.rdbuf();
		s.assign(out.str());
		_file << "<checksum>" << calcCheckSum(s)<< "</checksum>" << std::endl;
		return (true);
	}
	return (false);
}

bool	Saving::saveGame(const Map *map, const std::vector<Player *> &player, double timer)
{
	if (_fileName.compare(0, 18, "./ressources/maps/") == 0)
		_fileName = "./ressources/save/" + _fileName.substr(19, _fileName.length());
	_file.open(_fileName.c_str(), std::ofstream::out);
	if (_file.is_open())
	{
		saveMap(map);
		saveAllPlayer(player);
		saveTimer(timer);
		saveCheckSum();
		_file.close();
   		return (true);
  	}
  	return (false);
}

bool	Saving::saveGame(const Map *map)
{
	_file.open(_fileName.c_str(), std::ofstream::out);
	if (_file.is_open())
	{
		saveMap(map);
		saveCheckSum();
   		_file.close();
   		return (true);
  	}
  	return (false);
}

// GETTING SAVED MAP ///

double  Saving::convToDouble(const std::string &s) const
{
  std::istringstream iss(s);
  double        val = 0;

  iss >> val;
  return (val);
}

std::string	Saving::getData(const std::string& s, const std::string &s1)
{
	std::string 	ss("");
	size_t			pos;
	size_t			pos1 = 0;

	if ((pos = _fileRead.find(s.c_str())) != std::string::npos)
	{
		if ((pos1 = _fileRead.find(s1.c_str(), pos)) != std::string::npos)
		{
			ss.assign(_fileRead.substr(pos + s.length(), (pos1 - s.length()) - pos));
			_fileRead.replace(pos, (pos1 - pos + s1.length() + 1), "");
		}
	}
	return (ss);
}

double	Saving::getDataFromString(const std::string &s, const std::string &begin, const std::string &end)
{
	std::string 	ss;
	size_t			pos;
	size_t			pos1;

	if ((pos = s.find(begin.c_str())) != std::string::npos)
	{
		if ((pos1 = s.find(end.c_str())) != std::string::npos)
			ss.assign(s.substr(pos + begin.length(), pos1));
	}
	return (convToDouble(ss));
}

bool	Saving::getMapFromFile()
{
	int		size;
	bool	resume = true;

	size = convToDouble(getData("<size>", "</size>"));
	std::string s;
	_map = new Map(size, true);
	_map->setName(_fileName);
	while (resume)
	{
		s.assign(getData("<case>", "</case>"));
		if (s.size() > 0)
		{
			_map->addCube(((int)(getDataFromString(s, "<x>", "</x>"))), ((int)(getDataFromString(s, "<y>", "</y>"))), ((type)(getDataFromString(s, "<type>", "</type>"))));
		}
		else
			resume = false;
	}
	return (true);
}

bool	Saving::getPlayerFromFile()
{
	bool	resume = true;
	int 	id;
	std::string s;
	Player *player;

	while (resume)
	{
		s.assign(getData("<player>", "</player>"));
		if (s.size() > 0)
		{
			id = getDataFromString(s, "<id>", "</id>");
			std::pair<float, float>	pair;
			pair = std::make_pair<float, float>(getDataFromString(s, "<posx>", "</posx>"), getDataFromString(s, "<posy>", "</posy>"));
			if (id <= 2)
				player = new Player();
			else
				player = new Mybot();
			_player.push_back(player);
			if (id == 1 || id == 2)
			{
				player->setPlayer(id);
				_playerNb = id;
			}
			player->setId(id);
			player->initialize();
			player->setShield(getDataFromString(s, "<shield>", "</shield>"));
			player->setLife(getDataFromString(s, "<life>", "</life>"));
			player->setRange(getDataFromString(s, "<range>", "</range>"));
			player->setStock(getDataFromString(s, "<stock>", "</stock>"));
			player->setScore(getDataFromString(s, "<score>", "</score>"));
			player->setPos(pair);
		}
		else
			resume = false;
	}
	return (true);
}

bool	Saving::getTimerFromFile()
{
	std::string s;

	s.assign(getData("<timer>", "</timer>"));
	if (s.size() > 0)
	{
		_timer = convToDouble(s);
		return (true);
	}
	return (false);
}

bool	Saving::getSavedMap()
{
	std::ostringstream out;

	if (_extension == true)
	{
		_fileIn.open(_fileName.c_str(), std::ifstream::in);
		if (_fileIn.is_open())
		{
			out << _fileIn.rdbuf();
			_fileRead.assign(out.str());
			std::string s = getData("<checksum>", "</checksum>");
			std::string s1 = calcCheckSum(_fileRead);
			if (s.size() > 0 && s.compare(s1) == 0)
			{
				getMapFromFile();
				return (true);
			}
			else
			{
				std::cout << "BAD CHECKSUM" << std::endl;
				return (false);
			}
		}
		else
			std::cout << "FILE IS CLOSE" << std::endl;
	}
	return (false);
}

bool	Saving::getSavedGame()
{
	std::ostringstream out;

	if (_extension == true)
	{
		_fileIn.open(_fileName.c_str(), std::ifstream::in);
		if (_fileIn.is_open())
		{
			out << _fileIn.rdbuf();
			_fileRead.assign(out.str());
			std::string s = getData("<checksum>", "</checksum>");
			std::string s1 = calcCheckSum(_fileRead);
			if (s.size() > 0 && s.compare(s1) == 0)
			{
				getMapFromFile();
				getPlayerFromFile();
				getTimerFromFile();
				return (true);
			}
			else
			{
				std::cout << "BAD CHECKSUM" << std::endl;
				return (false);
			}
		}
		else
		{
			std::cout << "FILE IS CLOSE" << std::endl;
			return (false);
		}
	}
	return (false);
}

Map 	*Saving::getMap() const
{
	return (_map);
}

std::vector<Map*> 	*Saving::getMapList(std::vector<Saving *> &s)
{
	std::vector<Map *>	*v = new std::vector<Map *>;
	Map 				*m;

	for (std::vector<Saving *>::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		m = (*it)->getMap();
		if (m != NULL)
			v->push_back(m);
	}
	return (v);
}

std::vector<Player *>	&Saving::getPlayer()
{
	for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
	{
		(*it)->setPlayerTab(&_player);
		(*it)->setMap(_map);
	}
	return (_player);
}

std::vector<std::vector<Player *> >	*Saving::getPlayerList(std::vector<Saving *> &s)
{
	std::vector<std::vector<Player *> > *v = new std::vector<std::vector<Player *> >;

	for (std::vector<Saving *>::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		v->push_back((*it)->getPlayer());
	}
	return (v);
}

double 		Saving::getTimer() const
{
	return (_timer);
}

int 		Saving::getPlayerNb() const
{
	return (_playerNb);
}
