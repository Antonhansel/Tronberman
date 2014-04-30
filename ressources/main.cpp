#include <cstdlib>

#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <Geometry.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameEngine.hpp"
#include "Cube.hpp"

#include <iostream>

int		main()
{
	// On cree son engine
	GameEngine engine;

	// On l'initialise
	if (!engine.initialize())
	  {
	    std::cout << "engine init fail" << std::endl;
	    return EXIT_FAILURE;
	  }

	// On enable la depth car par defaut elle est pas active
	// Conseil : la mettre dans son game engine
	glEnable(GL_DEPTH_TEST);
	// la depth de clear par defaut sera 1
	glClearDepth(1.0f);
	// la couleur de clear par defaut sera du noir
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// pour creer un shader :
	// (un shader est un programe exectue par la carte graphique pour dessiner les pixels a l'ecan
	gdl::BasicShader shader;
	if (!shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) // le fragment shader se charge de dessiner les pixels
		|| !shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) // le vertex shader s'occupe de projeter les points sur l'ecran
		|| !shader.build()) // il faut ensuite builder son shader
	  {
	    std::cout << "load shader fail" << std::endl;
	    return EXIT_FAILURE;
	  }
	// pour utiliser un shader (pour que ce soit ce dernier qui dessine la geometrie) il faut le binder.
	// Un seul shader peut etre actif en mm temps
	shader.bind();

	Cube	myCube;
	gdl::Model	model;

	// on translate le cube en 1,0,1
	myCube.setTransformation(glm::translate(myCube.getTransformation(), glm::vec3(1, 0, 1)));
	// on scale le cube *1.5
	myCube.setTransformation(glm::scale(myCube.getTransformation(), glm::vec3(1.5f)));
	// on rotate le cube de 42 degres (en radians ^^) sur l'axe de y
	myCube.setTransformation(glm::rotate(myCube.getTransformation(), 0.733038286f, glm::vec3(0, 1, 0)));

	// il faut passer au shader la transformation de la camera (view)
	shader.setUniform("view", glm::lookAt(glm::vec3(0, 0, -2.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f)));
	// ... la projection de la camera (projection)
	shader.setUniform("projection", glm::perspective(60.f, 16.0f / 9.0f, 0.01f, 500.f));

	model.load("assets/marvin.fbx");
	model.setCurrentAnim(0);

	while (engine.update())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//myCube.draw(shader);
		model.draw(shader, glm::scale(glm::mat4(1), glm::vec3(0.005)), 1.0 / 60.0);
		engine.draw();
	}
	return EXIT_SUCCESS;
}
