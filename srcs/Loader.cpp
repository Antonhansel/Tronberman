/*
** Loader.cpp for Loader in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  09 10:46:17 2014 Antonin Ribeaud
** Last update Fri May  09 10:46:17 2014 Antonin Ribeaud
*/

#include "Loader.hpp"

Loader::Loader()
{
}

Loader::~Loader()
{
}

bool 	Loader::loadTextures()
{
  glm::vec3 vec = glm::vec3(0.0, 0.0, 1.0);

  _textures.resize(10, NULL);
	_textures[BLOCKD] = new gdl::Texture();
	if (_textures[BLOCKD]->load("./ressources/assets/BLOCKD.tga") == false)
		return (false);
	_textures[BORDER] = new gdl::Texture();
	if (_textures[BORDER]->load("./ressources/assets/BORDER.tga") == false)
		return (false);
	_textures[BLOCK] = new gdl::Texture();
	if (_textures[BLOCK]->load("./ressources/assets/BLOCK.tga") == false)
		return (false);
  _textures[BOMB] = new gdl::Texture();
  if (_textures[BOMB]->load("./ressources/assets/BOMB.tga") == false)
    return (false);
  _textures[LASER] = new gdl::Texture();
  if (_textures[LASER]->load("./ressources/assets/LASER.tga") == false)
    return (false);

  _textures[BLOCK]->bind();
	_geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushNormal(vec);
  // gauche
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  vec = glm::vec3(0.0, 0.0, 1.0);
  //face
  _geometry.setColor(glm::vec4(1, 1, 0, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

vec = glm::vec3(-1.0, 0.0, 0.0);
  _geometry.setColor(glm::vec4(1, 0, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

vec = glm::vec3(1.0, 0.0, 0.0);
//droite
  _geometry.setColor(glm::vec4(0, 1, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

vec = glm::vec3(0.0, 1.0, 0.0);
//dessus
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  // _geometry.setColor(glm::vec4(1, 0, 0, 1));
  // _geometry.pushNormal(vec);
  // _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  // _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  // _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  // _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  // _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  // _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  // _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  // _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
	return (true);
}

void Loader::drawGeometry(gdl::AShader &shader, glm::mat4 trans)
{
	_geometry.draw(shader, trans, GL_QUADS);
}

void 	Loader::bindTexture(type texttype)
{
	_textures[texttype]->bind();
}
