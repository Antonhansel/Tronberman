/*
** Particles.cpp for Particles in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon May  26 15:49:08 2014 Antonin Ribeaud
** Last update Mon May  26 15:49:08 2014 Antonin Ribeaud
*/

#include "Particles.hpp"
#include <sstream> 
#include <iostream>

Particles::Particles(Loader *loader)
{
  _loader = loader;
  reset();
  _texpart.load("./ressources/assets/BLOCKD.tga");
  _cubegeo.setColor(glm::vec4(1, 1, 1, 1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, 0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.setColor(glm::vec4(1, 1, 0, 1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, -0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.setColor(glm::vec4(1, 0, 1, 1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, 0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.setColor(glm::vec4(0, 1, 1, 1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, -0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.setColor(glm::vec4(1, 1, 1, 1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, 0.1, 0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.setColor(glm::vec4(1, 0, 0, 1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, -0.1));
  _cubegeo.pushVertex(glm::vec3(0.1, -0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, 0.1));
  _cubegeo.pushVertex(glm::vec3(-0.1, -0.1, -0.1));
  _cubegeo.pushUv(glm::vec2(0.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 0.0f));
  _cubegeo.pushUv(glm::vec2(1.0f, 1.0f));
  _cubegeo.pushUv(glm::vec2(0.0f, 1.0f));
  _cubegeo.build();
  _trigeo.setColor(glm::vec4(1, 1, 1, 1));
  _trigeo.pushVertex(glm::vec3(0.0, 0.5, 0.0));
  _trigeo.pushVertex(glm::vec3(-0.25, 0.0, 0.0));
  _trigeo.pushVertex(glm::vec3(0.25, 0.0, 0.0));
  _trigeo.pushUv(glm::vec2(0.0f, 0.0f));
  _trigeo.pushUv(glm::vec2(1.0f, 0.0f));
  _trigeo.pushUv(glm::vec2(0.0f, 1.0f));
  _trigeo.build();
  _display = true;
}

Particles::~Particles()
{}

void  Particles::reset()
{
  for (int i = 0; i < NUM_PARTICLES; i++)
    {
      particles[i].position[0] = 10.0;
      particles[i].position[1] = 0.0;
      particles[i].position[2] = 10.0;
      newSpeed(particles[i].speed);
    }
   for (int i = 0; i < NUM_DEBRIS; i++)
    {
      debris[i].position[0] = 10.0;
      debris[i].position[1] = 0.0;
      debris[i].position[2] = 10.0;

      debris[i].orientation[0] = 0.0;
      debris[i].orientation[1] = 0.0;
      debris[i].orientation[2] = 0.0;
      debris[i].scale[0] = (3.0 * 
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      debris[i].scale[1] = (3.0 * 
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      debris[i].scale[2] = (3.0 * 
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      
      newSpeed (debris[i].speed);
      newSpeed (debris[i].orientationSpeed);
    }
    fuel = 100;
}

void 	Particles::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _texpart.bind();
  if (fuel > 0)
  {
    for (int i = 0; i < NUM_PARTICLES; i++)
  	{
  		_transformation = glm::translate(glm::mat4(), glm::vec3(particles[i].position[0], particles[i].position[1], 
      particles[i].position[2]));
  	 _cubegeo.draw(shader, _transformation, GL_QUADS);
  	}
    for (int i = 0; i < NUM_DEBRIS; i++)
    {
      _transformation = glm::translate(glm::mat4(), glm::vec3(debris[i].position[0], debris[i].position[1], 
        debris[i].position[2]));
      _transformation = glm::scale(_transformation, glm::vec3(debris[i].scale[0], debris[i].scale[1], debris[i].scale[2]));
      _transformation = glm::rotate(_transformation, debris[i].orientation[0], glm::vec3(1, 0, 0));
      _transformation = glm::rotate(_transformation, debris[i].orientation[1], glm::vec3(0, 1, 0));
      _transformation = glm::rotate(_transformation, debris[i].orientation[2], glm::vec3(0, 0, 1));   
      _trigeo.draw(shader, _transformation, GL_TRIANGLES);
    }
  }
}

void 	Particles::update(gdl::Clock const &clock, gdl::Input &input)
{
    if (fuel > 0 && _display)
	   {
	  for (int i = 0; i < NUM_PARTICLES; i++)
	    {
	      particles[i].position[0] += particles[i].speed[0] * SPEED;
	      particles[i].position[1] += particles[i].speed[1] * SPEED;
	      particles[i].position[2] += particles[i].speed[2] * SPEED;
	     }
    for (int i = 0; i < NUM_DEBRIS; i++)
      {
        debris[i].position[0] += debris[i].speed[0] * 0.1;
        debris[i].position[1] += debris[i].speed[1] * 0.1;
        debris[i].position[2] += debris[i].speed[2] * 0.1;
        
        debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
        debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
        debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
      }
    fuel--;
    }
  if (input.getKey(SDLK_b))
      reset();
  if (input.getKey(SDLK_j))
      _display = !_display;
}

void Particles::newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;

  x = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
}
