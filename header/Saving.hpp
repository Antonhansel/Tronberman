#ifndef SAVING_HPP_
# define SAVING_HPP_

# include "Map.hpp"
# include "Md5.h"

class Saving
{
private:
	std::string				_fileName;
	std::ofstream			_file;
	std::ifstream			_fileIn;
	Map 					*_map;
	std::string				_fileRead;
	std::vector<Player *>	_player;
	bool					_extension;
	double 					_timer;
	int 					_playerNb;

public:
	Saving(const std::string &);
	~Saving();
	bool										getSavedMap();
	bool										getSavedGame();
	bool										saveGame(const Map *, const std::vector<Player *> &, const double &);
	bool										saveGame(const Map *);
	Map 										*getMap() const;
	static std::vector<Map *>					*getMapList(std::vector<Saving *> &);
	std::vector<Player*>						&getPlayer();
	static std::vector<std::vector<Player*> >   *getPlayerList(std::vector<Saving *> &);
	double 										getTimer() const;
	int 										getPlayerNb() const;

private:
	bool		saveMap(const Map *);
	bool		saveAllPlayer(const std::vector<Player *>&);
	bool		savePlayer(const Player *);
	bool		saveTimer(const double &);
	bool		getMapFromFile();
	bool		getPlayerFromFile();
	bool		getTimerFromFile();
	std::string getData(const std::string &, const std::string &);
	double		getDataFromString(const std::string &, const std::string &, const std::string &);
	double		convToDouble(const std::string &) const;
	std::string	calcCheckSum(std::string);
	bool		saveCheckSum();
};

#endif /* SAVING_HPP_ */
