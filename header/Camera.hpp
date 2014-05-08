/*
** Camera.hpp for Camera in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 19:25:34 2014 Antonin Ribeaud
// Last update Sat May  3 18:09:26 2014 Mehdi Chouag
*/

#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

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

using namespace gdl;
using namespace glm;

class Camera
{
public:
  Camera(const int, const int);
  ~Camera();
  void 			setPlayer(int players);
  BasicShader		&getShader();
  void 			stopContext();
  bool 			initScene();
  void 			flushContext();
  void 			update();
  void 			moveCamera(vec3, vec3, vec3, int);
  Clock 		&getClock();
  Input 		&getInput();
private:
  int			_width;
  int			_height;
  int 			_players;
  mat4			_transformation;
  mat4			_projection;
  SdlContext		_context;
  Clock			_clock;
  BasicShader		_shader;
  Input			_input;
};

#endif /*!_CAMERA_HPP_*/
