/*
** Intro.hpp for intro in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:53:12 2014 Antonin Ribeaud
** Last update Thu May  01 12:53:12 2014 Antonin Ribeaud
*/

/*
** core.hpp for Core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
** Last update Mon Apr  28 13:35:37 2014 Antonin Ribeaud
*/

#ifndef _INTRO_HPP_
# define _INTRO_HPP_

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
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"
# include <fmod.h>
 
#define MAX 32 
#define TAILLE_SPECTRE  8192
#define REF_FREQ 1000 /* Fréquence de référence */
#define REF_FREQ_EQ 171 /* Equivalent de REF_FREQ via FMOD_getSpectrum() */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class Intro : public gdl::Game
{
public:
	Intro();
	~Intro();
	bool			initialize();
	bool			update();
	void			draw();
	bool			makeCube(int, int, int);
	bool			drawLimits();
	bool			initFmod();
	bool 			genSpiral();
	bool			drawBackground();
private:
	int 				a[MAX][MAX];
	glm::mat4			_transformation;
	glm::mat4			_projection;
	float				_width;
	float				_height;
	gdl::SdlContext		_context;
	gdl::Clock			_clock;
	gdl::Input			_input;
	gdl::BasicShader	_shader;
	std::vector<AObject*> _objects;
	FMOD_SYSTEM 		*system;
  	FMOD_SOUND 			*musique;
  	FMOD_CHANNEL 		*canal;
  	FMOD_RESULT 		resultat;
  	float 	spectre[TAILLE_SPECTRE]; 
};

#endif /*!_INTRO_HPP_*/