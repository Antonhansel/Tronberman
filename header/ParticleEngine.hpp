/*
** ParticleEngine.hpp for particles in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon May  26 19:36:33 2014 Antonin Ribeaud
** Last update Mon May  26 19:36:33 2014 Antonin Ribeaud
*/

#ifndef _PARTICLES_HPP_
# define _PARTICLES_HPP_

# include <Clock.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <map>
# include "Loader.hpp"

# define NUM_PARTICLES 50	
# define SPEED 1.5
# define NUM_DEBRIS 50
# define COEFFSPEED 2
# define FUEL 150

class ParticleEngine
{
public:
	ParticleEngine(Loader *loader);
	~ParticleEngine();
	void 	draw(gdl::AShader &shader, gdl::Clock const &clock);
	void 	update(gdl::Clock const &clock, gdl::Input &input);
	void 	genParticles(glm::vec3 vec);
	void 	newSpeed (float dest[3]);
	void 	reset();
private:
	struct particleData
	{
	  float   position[3];
	  float   speed[3];
	};
	typedef struct particleData    particleData;
	struct debrisData
	{
	  float   position[3];
	  float   speed[3];
	  float   orientation[3];
	  float   orientationSpeed[3];
	  float   scale[3];
	};
typedef struct debrisData    debrisData;
	gdl::Geometry		_trigeo;
	int 				_partNumber;
	int 				_fuel;
	Loader				*_loader;
	glm::mat4 			_transpart;
	glm::mat4			_transdeb;
	particleData particles[NUM_PARTICLES];
	debrisData       debris[NUM_DEBRIS];
	bool _display;
};

#endif /*_PARTICLES_HPP_*/