/*
** CubeAnim.hpp for CubeAnim in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  14 14:57:44 2014 Antonin Ribeaud
** Last update Wed May  14 14:57:44 2014 Antonin Ribeaud
*/

#ifndef _CUBEANIM_HPP_
# define _CUBEANIM_HPP_

# include <math.h>
# include <fmod.h>
# include "Loader.hpp"
# include "Camera.hpp"
# include "Factory.hpp"
# include "AObject.hpp"
# include "BasicShader.hh"
# include <glm/glm.hpp>
# include <SdlContext.hh> 


#define MAX 32 
#define TAILLE_SPECTRE  2048
#define REF_FREQ 1000
#define REF_FREQ_EQ 171
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PI 3.14159

class CubeAnim
{
public:
	CubeAnim(Camera *, Loader *);
	~CubeAnim();
	bool 	makeCube(int x, int y, int z);
	float 	getEquation(int);
	void 	changeVolum(float);
	void 	rotate();
	bool 	genSpiral();
	void 	update();
	void 	draw(gdl::AShader &, type&);
	bool 	getStatus() const;
	void 	stopIntro(bool);
	bool 	initIntro();
	bool 	initFmod();
private:
	float			_angle;
  	float			_posy;
  	float			_posz;
  	float			_posx;
  	float			_xend;
	int			  _width;
  	int			  _height;
	Loader 		*_loader;
	Camera 		*_camera;
	std::vector<AObject*> _objects;
  	bool		_isLaunch;
  	bool 		_stopintro;
	int 		a[MAX][MAX];
	bool      	_inIntro;
  	FMOD_SYSTEM *system;
  	FMOD_SOUND 	*musique;
  	FMOD_CHANNEL *canal;
  	FMOD_RESULT resultat;
  	float		spectre[TAILLE_SPECTRE]; 
};

#endif /*_CUBEANIM_HPP_*/