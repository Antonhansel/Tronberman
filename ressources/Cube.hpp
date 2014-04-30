#pragma once

#include "AObject.hpp"

class Cube : public AObject
{
public:
	Cube()
	{
		// on la load
	  _texture.load("./assets/SunTexture.tga");

		_geometry.setColor(glm::vec4(1, 0, 0, 1)); // on set la color d'une premiere face
		// tout les push qui suivent seront de cette couleur

		// On y push les vertices d une premiere face
		_geometry.pushVertice(glm::vec3(0.5, -0.5, 0.5));
		_geometry.pushVertice(glm::vec3(0.5, 0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, -0.5, 0.5));

		// Les UVs d'une premiere face
		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		// ETC ETC
		_geometry.setColor(glm::vec4(0, 1, 0, 1));

		_geometry.pushVertice(glm::vec3(0.5, -0.5, -0.5));
		_geometry.pushVertice(glm::vec3(0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(-0.5, -0.5, -0.5));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		_geometry.setColor(glm::vec4(0, 0, 1, 1));

		_geometry.pushVertice(glm::vec3(0.5, -0.5, -0.5));
		_geometry.pushVertice(glm::vec3(0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(0.5, 0.5, 0.5));
		_geometry.pushVertice(glm::vec3(0.5, -0.5, 0.5));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		_geometry.setColor(glm::vec4(0, 1, 1, 1));

		_geometry.pushVertice(glm::vec3(-0.5, -0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(-0.5, -0.5, -0.5));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		_geometry.setColor(glm::vec4(1, 0, 1, 1));

		_geometry.pushVertice(glm::vec3(0.5, 0.5, 0.5));
		_geometry.pushVertice(glm::vec3(0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, -0.5));
		_geometry.pushVertice(glm::vec3(-0.5, 0.5, 0.5));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		_geometry.setColor(glm::vec4(1, 1, 0, 1));

		_geometry.pushVertice(glm::vec3(0.5, -0.5, -0.5));
		_geometry.pushVertice(glm::vec3(0.5, -0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, -0.5, 0.5));
		_geometry.pushVertice(glm::vec3(-0.5, -0.5, -0.5));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));


		// Tres important, on n'oublie pas de build la geometrie pour envoyer ses informaitions aux GPU
		_geometry.build();
	}

	virtual ~Cube()
	{}

	virtual void draw(gdl::AShader &shader)
	{
		// on bind le shader
		shader.bind();
		// on indique que l on veut binder la texture en position 0
		glActiveTexture(GL_TEXTURE0);
		_texture.bind(); // on bind la texture avant le draw
		_geometry.draw(shader, _transformation, GL_QUADS); // la geometry est composee de quads
		// si elle avait et compose de triangles l'argument aurait ete GL_TRIANGLES
	}

	private:
		gdl::Geometry	_geometry; // la geometry a dessiner
};
