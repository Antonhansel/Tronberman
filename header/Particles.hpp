/*
** Particles.hpp for particles in /home/apollo/rendu/cpp_bomberman/header
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

# define NUM_PARTICLES    1000
# define SPEED 	1
class Particles
{
public:
	Particles();
	~Particles();
	void 	draw(gdl::AShader &shader, gdl::Clock const &clock);
	void 	update(gdl::Clock const &clock);
	void 	genParticles(glm::vec3 vec);
	void 	newSpeed (float dest[3]);
private:
	struct particleData
	{
	  float   position[3];
	  float   speed[3];
	  float   color[3];
	};
	typedef struct particleData    particleData;
	gdl::Geometry 		_geometry;
	int 		_partNumber;
	int 		fuel;
	particleData particles[NUM_PARTICLES];
};

#endif /*_PARTICLES_HPP_*/