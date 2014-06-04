/*
** ParticleEngine.hpp for particles in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon May  26 19:36:33 2014 Antonin Ribeaud
** Last update Mon May  26 19:36:33 2014 Antonin Ribeaud
*/

#ifndef _PARTICLEENGINE_HPP_
# define _PARTICLEENGINE_HPP_

# include <Clock.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include "Particles.hpp"

class ParticleEngine
{
public:
	ParticleEngine(Loader *loader);
	~ParticleEngine();
	void 	draw(gdl::AShader &shader, gdl::Clock const &clock, AObject *);
	void 	update(gdl::Clock const &clock, gdl::Input &input);
	void 	spawnParticles(glm::vec3 &vec);
	void 	cleanParticles();
	bool 	canDraw(std::pair<float, float>, std::pair<float, float>);

	std::vector<Particles *> 	_exploList;
private:
	Loader				*_loader;
};

#endif /*_PARTICLEENGINE_HPP_*/
