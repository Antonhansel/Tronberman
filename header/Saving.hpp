#ifndef _SAVING_HPP_
# define _SAVING_HPP_

# include "Map.hpp"
# include "Player.hpp"
# include "AObject.hpp"

class Saving
{
private:
	std::string							_name;
	std::vector<std::pair<int, int> >	_spawn;
	AObject								**_map;
	int									_sizeMap;
	int									_nbrPlayer;
	int									_nbrBot;
	bool								_isGood;
	int									_nbrLine;

public:
	Saving(std::string &);
	~Saving();
	bool    loadSize(std::list<std::string> &);
	bool    loadCase(std::list<std::string> &);
	bool    loadSpawn(std::list<std::string> &);
	bool    loadMap(std::string &);
	void	myParseur(std::vector<int> &, std::string &);
	bool	myBalise(std::string &, std::string &, std::string &, std::string &);
	Map 	*returnMap();
};

#endif /* !_SAVING_HPP_ */