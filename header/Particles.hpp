/*
** Particles.hpp for Particles in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  28 18:59:00 2014 Antonin Ribeaud
** Last update Wed May  28 18:59:00 2014 Antonin Ribeaud
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
# include "Loader.hpp"

# define NUM_PARTICLES 30
# define SPEED 1.5
# define NUM_DEBRIS 30
# define COEFFSPEED 2
# define FUEL 50

class Particles
{
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
	int 				_fuel;
	Loader				*_loader;
	glm::mat4 			_transpart;
	glm::mat4			_transdeb;
	particleData 	_particles[NUM_PARTICLES];
	debrisData       _debris[NUM_DEBRIS];
	std::pair<float, float> _pos;
public:
	Particles(Loader *loader, glm::vec3 &);
	~Particles();
	void 	draw(gdl::AShader &shader);
	void 	update();
	int 	getFuel() const;
	void 	newSpeed(float dest[3]);
	std::pair<float, float> getPos() const;
};

#endif /*!PARTICLES_HPP_*/