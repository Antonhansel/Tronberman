#ifndef _SAVING_HPP_
# define _SAVING_HPP_

# include "Core.hpp"

class Saving
{
private:
	std::string							_name;
	std::vector<std::pair<int, int> >	_spawn;
	std::vector<Map *>					_listMap;
	std::map<int, Player*>				_player;
	std::ofstream						_file;
	AObject								**_map;
	int									_sizeMap;
	int									_nbrPlayer;
	int									_nbrBot;
	bool								_isGood;
	int									_nbrLine;

public:
	Saving(std::vector<std::string> &);
	Saving(std::string &, Core *);
	~Saving();
	bool    loadSize(std::list<std::string> &);
	bool    loadCase(std::list<std::string> &);
	bool    loadSpawn(std::list<std::string> &);
	bool    loadMap(std::string &);
	void	myParseur(std::vector<int> &, std::string &);
	bool	myBalise(std::string &, std::string &, std::string &, std::string &);
	std::vector<Map *>     getListMap();
	void	addListMap();

public:
	bool	saveSpawn();
	bool	saveMap();
	bool	savePlayer();
};

#endif /* !_SAVING_HPP_ */