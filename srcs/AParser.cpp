#include "AParser.hpp"


AParser::AParser()
{
	
}

AParser::~AParser()
{
	
}

void        AParser::my_parseur(std::vector<int> &tab, std::string &str)
{
  unsigned int   x;
  unsigned int   y;
  int v;
  tab.clear();

  x = 0;
  y = 0;
  while (str[y])
  {
    if (str[y] == ' ')
    {
      std::istringstream buffer(str.substr(x, y - x + 1));
      buffer >> v;
      tab.push_back(v);
      x = y + 1;
    }
    y++;
  }
    std::istringstream buffer(str.substr(x, y - x + 1));
    buffer >> v;
    tab.push_back(v);
}

bool        AParser::my_balise(std::string &in, std::string &out, std::string &str)
{
  unsigned int pos = str.find(in) + in.length();
  unsigned int pos2 = str.find(out);

  if (pos2 != std::string::npos)
    str = str.substr(pos, pos2 - pos);
  else
    str = str.substr(pos);
  return (true);
}
