#include <iostream>
#include <map>

int main ()
{
  std::map< <std::pair<float, float> ,int> mymap;
  
  std::pair<float, float> pos;

  pos.first = 0;
  pos.second = 0;
  mymap[pos] = 50;

  if (mymap.find(pos) != mymap.end())
    std::cout << "c => " << mymap.find(pos)->second << '\n';

  return 0;
}
