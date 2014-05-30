/*
** Particles.cpp for Particles in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  28 18:41:58 2014 Antonin Ribeaud
** Last update Wed May  28 18:41:58 2014 Antonin Ribeaud
*/

#include "Particles.hpp"

Particles::Particles(Loader *loader, glm::vec3 &vec)
{
	_loader = loader;
	  for (int i = 0; i < NUM_PARTICLES; i++)
    {
      _particles[i].position[0] = vec.x;
      _particles[i].position[1] = vec.y;
      _particles[i].position[2] = vec.z;
      newSpeed(_particles[i].speed);
    }
   for (int i = 0; i < NUM_DEBRIS; i++)
    {
      _debris[i].position[0] = vec.x;
      _debris[i].position[1] = vec.y;
      _debris[i].position[2] = vec.z;

      _debris[i].orientation[0] = 0.0;
      _debris[i].orientation[1] = 0.0;
      _debris[i].orientation[2] = 0.0;
      _debris[i].scale[0] = (3.0 * 
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      _debris[i].scale[1] = (3.0 *
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      _debris[i].scale[2] = (3.0 *
          ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

      newSpeed(_debris[i].speed);
      newSpeed(_debris[i].orientationSpeed);
    }
	_fuel = FUEL;
  _pos.first = vec.x;
  _pos.second = vec.z;
}

Particles::~Particles()
{

}

void 	Particles::draw(gdl::AShader &shader)
{
  if (_fuel > 0)
  {
    for (int i = 0; i < NUM_PARTICLES; i++)
  	{
  	  _transpart = glm::translate(glm::mat4(), glm::vec3(_particles[i].position[0], _particles[i].position[1], 
      _particles[i].position[2]));
      _transpart = glm::scale(_transpart, glm::vec3(0.3, 0.3, 0.3));
      _loader->drawGeometry(shader, _transpart);
  	}
    for (int i = 0; i < NUM_DEBRIS; i++)
    {
      _transdeb = glm::translate(glm::mat4(), glm::vec3(_debris[i].position[0], _debris[i].position[1], 
      _debris[i].position[2]));
      _transdeb = glm::scale(_transdeb, glm::vec3(_debris[i].scale[0], _debris[i].scale[1], _debris[i].scale[2]));
      _transdeb = glm::rotate(_transdeb, _debris[i].orientation[0], glm::vec3(1, 0, 0));
      _transdeb = glm::rotate(_transdeb, _debris[i].orientation[1], glm::vec3(0, 1, 0));
      _transdeb = glm::rotate(_transdeb, _debris[i].orientation[2], glm::vec3(0, 0, 1));
      _loader->drawParticules(shader, _transdeb);
    }
  }
}

void 	Particles::update()
{
    if (_fuel > 0)
	   {
	  for (int i = 0; i < NUM_PARTICLES; i++)
	    {
	      _particles[i].position[0] += _particles[i].speed[0] * SPEED;
	      _particles[i].position[1] += _particles[i].speed[1] * SPEED;
	      _particles[i].position[2] += _particles[i].speed[2] * SPEED;
	     }
    for (int i = 0; i < NUM_DEBRIS; i++)
      {
        _debris[i].position[0] += _debris[i].speed[0] * 0.1;
        _debris[i].position[1] += _debris[i].speed[1] * 0.1;
        _debris[i].position[2] += _debris[i].speed[2] * 0.1;
        
        _debris[i].orientation[0] += _debris[i].orientationSpeed[0] * 10;
        _debris[i].orientation[1] += _debris[i].orientationSpeed[1] * 10;
        _debris[i].orientation[2] += _debris[i].orientationSpeed[2] * 10;
      }
    _fuel--;
    }
}

int 	Particles::getFuel() const
{
	return (_fuel);
}

void 	Particles::newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;

  x = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (COEFFSPEED * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  dest[0] = x;
  dest[1] = abs(y);
  dest[2] = z;
}

std::pair<float, float> Particles::getPos() const
{
  return (_pos);
}