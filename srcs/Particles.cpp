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
  _partNumber = 0;
  int    i;

  for (i = 0; i < NUM_PARTICLES; i++)
    {
      particles[i].position[0] = 0.0;
      particles[i].position[1] = 0.0;
      particles[i].position[2] = 0.0;
      particles[i].color[0] = 1;
      particles[i].color[1] = 1;
      particles[i].color[2] = 1;
      newSpeed (particles[i].speed);
    }
  // for (i = 0; i < NUM_DEBRIS; i++)
  //   {
  //     debris[i].position[0] = 0.0;
  //     debris[i].position[1] = 0.0;
  //     debris[i].position[2] = 0.0;
  //     debris[i].orientation[0] = 0.0;
  //     debris[i].orientation[1] = 0.0;
  //     debris[i].orientation[2] = 0.0;
  //     debris[i].color[0] = 0.7;
  //     debris[i].color[1] = 0.7;
  //     debris[i].color[2] = 0.7;
  //     debris[i].scale[0] = (2.0 * 
		// 	    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  //     debris[i].scale[1] = (2.0 * 
		// 	    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  //     debris[i].scale[2] = (2.0 * 
		// 	    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  //    newSpeed(debris[i].speed);
  //    newSpeed(debris[i].orientationSpeed);
  //   }
  fuel = 100;
}

Particles::~Particles()
{

}

void 	Particles::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  	int    i;
   	glPushMatrix();
   	glDisable (GL_DEPTH_TEST);
    glBegin (GL_POINTS);
    for (i = 0; i < NUM_PARTICLES; i++)
	{
	  glColor3fv (particles[i].color);
	  glVertex3fv (particles[i].position);
	}  
    glEnd ();
    // glPopMatrix ();
    // glEnable(GL_DEPTH_TEST);
    glNormal3f(0.0, 0.0, 1.0);

 //    for (i = 0; i < NUM_DEBRIS; i++)
	// {
	//   glColor3fv(debris[i].color);

	//   glPushMatrix();
      
	//   glTranslatef(debris[i].position[0],
	// 		debris[i].position[1],
	// 		debris[i].position[2]);

	//   glRotatef(debris[i].orientation[0], 1.0, 0.0, 0.0);
	//   glRotatef(debris[i].orientation[1], 0.0, 1.0, 0.0);
	//   glRotatef(debris[i].orientation[2], 0.0, 0.0, 1.0);

	//   glScalef (debris[i].scale[0],
	// 	    debris[i].scale[1],
	// 	    debris[i].scale[2]);
	//   	// _geometry.setColor(glm::vec4(1, 1, 1, 1));
 //  		// _geometry.pushVertex(glm::vec3(0.0, 0.5, 0.0));
 //  		// _geometry.pushVertex(glm::vec3(-0.25, 0.0, 0.0));
 //  		// _geometry.pushVertex(glm::vec3(0.25, 0.0, 0.0));
 //  		// _geometry.build();

	//   glBegin(GL_TRIANGLES);
	//   glVertex3f (0.0, 0.5, 0.0);
	//   glVertex3f (-0.25, 0.0, 0.0);
	//   glVertex3f (0.25, 0.0, 0.0);
	//   glEnd ();
	//   glPopMatrix ();
	//   std::cout << "TEST" << std::endl;
	// }
    //glEnable(GL_DEPTH_TEST);
}

void 	Particles::update(gdl::Clock const &clock)
{
	int    i;

    if (fuel > 0)
	{
		std::cout << fuel << std::endl;
	  for (i = 0; i < NUM_PARTICLES; i++)
	    {
	      particles[i].position[0] += particles[i].speed[0] * 0.2;
	      particles[i].position[1] += particles[i].speed[1] * 0.2;
	      particles[i].position[2] += particles[i].speed[2] * 0.2;
	  }
	      
	 //      particles[i].color[0] -= 1.0 / 500.0;
	 //      if (particles[i].color[0] < 0.0)
		// {
		//   particles[i].color[0] = 0.0;
		// }
	      
	 //      particles[i].color[1] -= 1.0 / 100.0;
	 //      if (particles[i].color[1] < 0.0)
		// {
		//   particles[i].color[1] = 0.0;
		// }
	      
	 //      particles[i].color[2] -= 1.0 / 50.0;
	 //      if (particles[i].color[2] < 0.0)
		// {
		//   particles[i].color[2] = 0.0;
		// }
	 //    }	  
	  for (i = 0; i < NUM_DEBRIS; i++)
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
	// else
	// 	delete this;
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
