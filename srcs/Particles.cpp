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

Particles::Particles()
{
  for (int i = 0; i < NUM_PARTICLES; i++)
    {
      particles[i].position[0] = 5.0;
      particles[i].position[1] = 0.0;
      particles[i].position[2] = 5.0;
      particles[i].color[0] = 1000;
      particles[i].color[1] = 1000;
      particles[i].color[2] = 1000;
      newSpeed(particles[i].speed);
    }
  fuel = 100;
}

Particles::~Particles()
{}

void 	Particles::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  	int    i;
   	glPushMatrix();
   	glDisable(GL_DEPTH_TEST);
    glBegin(GL_POINTS);
    glColor3ub(255,255,255);
    for (i = 0; i < NUM_PARTICLES; i++)
	{
	  //glColor3fv(particles[i].color);
	  glVertex3fv(particles[i].position);
	}
    glEnd();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);	
}

void 	Particles::update(gdl::Clock const &clock)
{
	int    i;

    if (fuel > 0)
	{
	  for (i = 0; i < NUM_PARTICLES; i++)
	    {
	      particles[i].position[0] += particles[i].speed[0] * SPEED;
	      particles[i].position[1] += particles[i].speed[1] * SPEED;
	      particles[i].position[2] += particles[i].speed[2] * SPEED;
	  }
	      
	      particles[i].color[0] -= 1.0 / 500.0;
	      if (particles[i].color[0] < 0.0)
		{
		  particles[i].color[0] = 1.0;
		}
	      
	      particles[i].color[1] -= 1.0 / 100.0;
	      if (particles[i].color[1] < 0.0)
		{
		  particles[i].color[1] = 1.0;
		}
	      
	      particles[i].color[2] -= 1.0 / 50.0;
	      if (particles[i].color[2] < 0.0)
		{
		  particles[i].color[2] = 1.0;
		}
	  }	  
	 fuel--;
}

void Particles::newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;

  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
}
