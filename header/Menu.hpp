//
// Menu.hpp for Menu in /home/chouag_m/rendu/old
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat May  3 17:42:13 2014 Mehdi Chouag
// Last update Mon May  5 13:15:09 2014 Mehdi Chouag
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
# include <math.h>
# include <fmod.h>
# include "AObject.hpp"
# include "Cube.hpp"
# include "Factory.hpp"
 
#define MAX 32 
#define TAILLE_SPECTRE  2048
#define REF_FREQ 1000
#define REF_FREQ_EQ 171
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PI 3.14159

using namespace gdl;
using namespace glm;

class Menu : public Game
{
public:
  Menu(Camera *);
  ~Menu();
  bool			initialize();
  bool			update();
  void			reset();
  void			draw();
  bool			launch() const;
  bool			makeCube(int, int, int);
  bool			initFmod();
  bool 			genSpiral();
  float		        getEquation(int);
  void			rotate();
  
private:
  Camera		*_camera;
  int 			a[MAX][MAX];
  Clock			_clock;
  Input			_input;
  BasicShader		_shader;
  std::vector<AObject*> _objects;
  bool			_isLaunch;
  int			_width;
  int			_height;
  float			_angle;
  float			_posy;
  float			_posz;
  float			_posx;

private:
  FMOD_SYSTEM 		*system;
  FMOD_SOUND 		*musique;
  FMOD_CHANNEL 		*canal;
  FMOD_RESULT 		resultat;
  float			spectre[TAILLE_SPECTRE]; 
};

#endif /* !MENU_HPP_ */
