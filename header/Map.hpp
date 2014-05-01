#ifndef MAP_HPP
# define MAP_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <map>
# include <stdlib.h>
# include <utility>
# include "Case.hpp"


class Map
{
public:
	Map(const int&, const int&);
	Map(const std::string&);

	void				outline();
	void				spawnBot();
	void				drawWall();
	std::map< std::pair<int, int>, Case *>	getCases();
	bool				spawnBotChecking(const int&, const int&);
	bool				isEmpty(const int&, const int&);
	~Map();

private:
	int					size_x;
	int					size_y;
	std::map< std::pair<int, int>, Case *>	cases;	
};

#endif /* !MAP_HPP */