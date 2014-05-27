#ifndef _SAVING_HPP_
# define _SAVING_HPP_

# include "Core.hpp"

//class Player;

class Saving
{
private:
	std::string							_name;
	std::vector<std::pair<int, int> >	_spawn;
	std::vector<Map *>					_listMap;
	std::map<int, Player*>				_player;
	std::vector< std::map<int, Player*>	> _players;
	std::ofstream						_file;
	AObject								**_map;
	int									_sizeMap;
	int									_nbrPlayer;
	int									_nbrBot;
	bool								_isGood;
	int									_nbrLine;

public:
	Saving(std::vector<std::string> &);
	Saving(std::string, Core *);
	Saving(std::string &fileName, AObject **, int);
	~Saving();

	bool    loadRange(std::list<std::string> &, Player *);
	bool    loadStock(std::list<std::string> &, Player *);
	bool    loadLife(std::list<std::string> &, Player *);
	bool    loadId(std::list<std::string> &, Player *);
	bool    loadType(std::list<std::string> &, Player *);
	bool    loadPlayer(std::string &);

	bool    loadSize(std::list<std::string> &);
	bool    loadCase(std::list<std::string> &);
	bool    loadSpawn(std::list<std::string> &);
	bool    loadMap(std::string &);
	void	myParseur(std::vector<int> &, std::string &);
	bool	myBalise(std::string &, std::string &, std::string &, std::string &);
	std::vector<Map *>		getListMap();
	std::vector<Map *>		getCostumListMap();
	std::vector< std::map<int, Player *> >    getListPlayer();
	void	addListMap();
	void	addListPlayer();

public:
	bool	saveSpawn();
	bool	saveMap();
	bool	savePlayer();
};

#endif /* !_SAVING_HPP_ */