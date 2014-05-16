//
// Menu.hpp for Menu in /home/chouag_m/rendu/old
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat May  3 17:42:13 2014 Mehdi Chouag
// Last update Tue May 13 19:24:11 2014 Mehdi Chouag
//

#ifndef MENU_HPP_
# define MENU_HPP_

# include "Camera.hpp"
# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <Model.hh> 
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>
# include "CubeAnim.hpp"
# include "Loader.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Cube.hpp"
# include "Factory.hpp"
# include "Text.hpp"

using namespace gdl;
using namespace glm;

class Menu : public Game
{
public:
  Menu(Camera *, Loader *);
  ~Menu();
  bool			initialize();
  bool			update();
  void			reset();
  void			draw();
  bool			launch() const;
  bool      drawBackground();
private:
  int         _isSelect;
  CubeAnim *_cubeanim;
  Background *_background;
  Camera		*_camera;
  bool      _stopIntro;
  Loader    *_loader;
  Clock			_clock;
  Input			_input;
  BasicShader		_shader;
  Text			*_text;
  int       _players;
  bool      _isLaunch;
  std::map<std::pair<int, int>, std::vector<gdl::Geometry *> > _step1;
};

#endif /* !MENU_HPP_ */
