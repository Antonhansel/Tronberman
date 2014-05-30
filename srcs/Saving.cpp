#include "Saving.hpp"

Saving::Saving(const std::string &fileName) :
	_fileName(fileName)
{
	std::cout << "Saving..." << std::endl;
	_map = NULL;
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
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				ao = m->getCase(x, y);
				if (ao != NULL)
					_file << "<case><x>" << x << "</x><y>" << y << "</y><type>" <<  ao->getType() << "</type></case>" << std::endl;
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

bool	Saving::saveAllPlayer(const std::map<int, Player *> &p)
{
	for (std::map<int, Player *>::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		if (!savePlayer((*it).second))
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

bool	Saving::saveGame(const Map *map, const std::map<int, Player *> &player, double timer)
{
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
			_fileRead.replace(pos, pos1, "");
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
	_map = new Map(size, false);
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

	while (resume)
	{
		s.assign(getData("<player>", "</player>"));
		if (s.size() > 0)
		{
			std::cout << "X = " << getDataFromString(s, "<x>", "</x>");
			id = getDataFromString(s, "<id>", "</id>");
			std::pair<float, float>	pair;
			pair = std::make_pair<float, float>(getDataFromString(s, "<posx>", "</posx>"), getDataFromString(s, "<posy>", "</posy>"));
			_player[id] = new Player();
			_player[id]->setShield(getDataFromString(s, "<shield>", "</shield>"));
			_player[id]->setLife(getDataFromString(s, "<life>", "</life>"));
			_player[id]->setRange(getDataFromString(s, "<range>", "</range>"));
			_player[id]->setStock(getDataFromString(s, "<stock>", "</stock>"));
			_player[id]->setScore(getDataFromString(s, "<score>", "</score>"));
			_player[id]->setPos(pair);
		}
		else
			resume = false;
	}
	return (true);
}

void	Saving::getSavedMap()
{
	std::ostringstream out;

	_fileIn.open(_fileName.c_str(), std::ifstream::in);
	if (_fileIn.is_open())
	{
		out << _fileIn.rdbuf();
		_fileRead.assign(out.str());
		std::string s = getData("<checksum>", "</checksum>");
		std::string s1 = calcCheckSum(_fileRead);
		//std::cout << "Checksum ==> " << s << " && " << s1 << std::endl;
		if (s.compare(s1) == 0)
			getMapFromFile();
		else
			std::cout << "BAD CHECKSUM" << std::endl;
	}
	else
		std::cout << "FILE IS CLOSE" << std::endl;
}

void	Saving::getSavedGame()
{
	std::ostringstream out;

	_fileIn.open(_fileName.c_str(), std::ifstream::in);
	if (_fileIn.is_open())
	{
		out << _fileIn.rdbuf();
		_fileRead.assign(out.str());
		std::string s = getData("<checksum>", "</checksum>");
		std::string s1 = calcCheckSum(_fileRead);
		if (s.compare(s1) == 0)
		{
			getMapFromFile();
			getPlayerFromFile();
		}
		else
			std::cout << "BAD CHECKSUM" << std::endl;

	}
	else
		std::cout << "FILE IS CLOSE" << std::endl;
}

Map 	*Saving::getMap() const
{
	return (_map);
}

std::vector<Map*> 	Saving::getMapList(std::vector<Saving *> &s)
{
	std::vector<Map *>	v;
	Map 				*m;

	for (std::vector<Saving *>::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		m = (*it)->getMap();
		if (m != NULL)
			v.push_back(m);
	}
	return (v);
}

std::map<int, Player *>	Saving::getPlayer() const
{
	return (_player);
}

std::vector<std::map<int, Player *> >	Saving::getPlayerList(std::vector<Saving *> &s)
{
	std::vector<std::map<int, Player *> > v;

	for (std::vector<Saving *>::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		v.push_back((*it)->getPlayer());
	}
	return (v);
}