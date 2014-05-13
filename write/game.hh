#ifndef GAME_HH
#define GAME_HH

#include <OpenGL.hh>
#include <Game.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Model.hh>
#include <iostream>
#include <BasicShader.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>

class Game : public gdl::Game
{
public:
  Game(gdl::SdlContext &context);
  bool initialize();
  bool update();
  void draw();
  int	getColumn(char);
  void	putchar(char, std::vector<gdl::Geometry *>&);
  void	putstr(char *, int, int);
  virtual ~Game();

private:
  gdl::SdlContext &context;
  gdl::Input input;
  gdl::Texture backgroundTexture;
  gdl::BasicShader shader;
  gdl::Geometry geometry;
  gdl::Texture texture;
  int	        _firstChar;
  std::map<std::pair<int, int >, std::vector<gdl::Geometry *> > _menu;
};

#endif /* end of include guard: GAME_HH */
