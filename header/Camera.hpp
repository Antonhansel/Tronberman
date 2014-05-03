/*
** Camera.hpp for Camera in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 19:25:34 2014 Antonin Ribeaud
** Last update Fri May  02 19:25:34 2014 Antonin Ribeaud
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

class Camera
{
public:
	Camera();
	~Camera();
	void 			setPlayer(int players);
	gdl::BasicShader &getShader();
	void 			stopContext();
	bool 			initScene();
	bool 			flushContext();
	void 			update();
	bool 			moveCameraP1(glm::vec3, glm::vec3, glm::vec3);
	bool 			moveCameraP2(glm::vec3, glm::vec3, glm::vec3);
	gdl::Clock 		&getClock();
	gdl::Input 		&getInput();
private:
	int 				_players;
	glm::mat4			_transformation;
	glm::mat4			_projection;
	gdl::SdlContext		_context;
	gdl::Clock			_clock;
	gdl::BasicShader	_shader;
	gdl::Input			_input;
};

#endif /*!_CAMERA_HPP_*/