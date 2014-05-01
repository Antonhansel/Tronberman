#ifndef MAP_HPP
# define MAP_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <list>
# include <stdlib.h>
# include "Case.hpp"


class Map
{
public:
	Map(const int&, const int&);
	Map(const std::string&);

	void				outline();
	void				spawn_bot();
	void				draw_wall();
	std::list<Case *>	getCases();
	bool				spawn_bot_checking(const int&, const int&);
	bool				isEmpty(const int&, const int&);
	~Map();

private:
	int					size_x;
	int					size_y;
	std::list<Case *>	cases;	
};

#endif /* !MAP_HPP */