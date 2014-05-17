#ifndef _APARSER_HPP_
# define _APARSER_HPP_

# include <sstream>
# include <iostream>
# include <fstream>
# include <vector>

class AParser
{
public:
	AParser();
	~AParser();
	void    my_parseur(std::vector<int> &, std::string &);
	bool    my_balise(std::string &, std::string &, std::string &);
};

#endif /* !APARSER_HPP */