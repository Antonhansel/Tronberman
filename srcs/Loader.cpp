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
  _modelCount = 0;
}

Loader::~Loader()
{
}

bool 	Loader::loadTextures()
{
  glm::vec3 vec = glm::vec3(0.0, 0.0, 1.0);

  _textures.resize(20, NULL);
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
  _textures[UNSELECTED] = new gdl::Texture();
  if (_textures[UNSELECTED]->load("./ressources/fonts/blue.tga") == false)
    return (false);
  _textures[SELECTED] = new gdl::Texture();
  if (_textures[SELECTED]->load("./ressources/fonts/red.tga") == false)
    return (false);
   _textures[BONUSV] = new gdl::Texture();
  if (_textures[BONUSV]->load("./ressources/assets/BONUS1.tga") == false)
    return (false);
  _textures[BONUSB] = new gdl::Texture();
  if (_textures[BONUSB]->load("./ressources/assets/BONUS2.tga") == false)
    return (false);
  _textures[BONUSR] = new gdl::Texture();
  if (_textures[BONUSR]->load("./ressources/assets/BONUS3.tga") == false)
    return (false);
  _models.resize(5, NULL);
  _models[1] = new gdl::Model();
  if (_models[1]->load( "./ressources/assets/anim/bomberman_white_run.FBX") == false)
    {
        std::cout << "Error on loading model" << std::endl;
        return (false);
    }
  _models[2] = new gdl::Model();
  if (_models[2]->load("./ressources/assets/anim/bomberman_black_run.FBX") == false)
    {
        std::cout << "Error on loading model" << std::endl;
        return (false);
    }
  _models[3] = new gdl::Model();
  if (_models[3]->load("./ressources/assets/anim/bomberman_blue_run.FBX") == false)
    {
        std::cout << "Error on loading model" << std::endl;
        return (false);
    }
  _models[4] = new gdl::Model();
  if (_models[4]->load("./ressources/assets/anim/bomberman_gold_run.FBX") == false)
    {
        std::cout << "Error on loading model" << std::endl;
        return (false);
    }
  _textures[BLOCKD]->bind();
  // GLfloat no_mat[] = { 0.0F,0.0F,0.0F,1.0F };
  // GLfloat mat_ambient_color[] = { 0.8F,0.8F,0.2F,1.0F };
  // GLfloat mat_diffuse[] = { 0.1F,0.5F,0.8F,1.0F };
  // GLfloat no_shininess[] = { 0.0F };
  // GLfloat mat_emission[] = {0.3F,0.2F,0.2F,0.0F};
  // glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color);
  // glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  // glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
  // glMaterialfv(GL_FRONT,GL_SHININESS,no_shininess);
  // glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
	_geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  pushTexture(&_geometry);

  vec = glm::vec3(0.0, 0.0, 1.0);
  //face
  _geometry.setColor(glm::vec4(1, 1, 0, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushTexture(&_geometry);

  vec = glm::vec3(-1.0, 0.0, 0.0);
  _geometry.setColor(glm::vec4(1, 0, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  pushTexture(&_geometry);

  vec = glm::vec3(1.0, 0.0, 0.0);
  _geometry.setColor(glm::vec4(0, 1, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushTexture(&_geometry);

  vec = glm::vec3(0.0, 1.0, 0.0);
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushNormal(vec);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  pushTexture(&_geometry);
  _geometry.build();
  loadParticules();
	return (true);
}

void  Loader::loadParticules()
{
  _trigeo.setColor(glm::vec4(1, 1, 1, 1));
  _trigeo.pushVertex(glm::vec3(0.0, 0.5, 0.0));
  _trigeo.pushVertex(glm::vec3(-0.25, 0.0, 0.0));
  _trigeo.pushVertex(glm::vec3(0.25, 0.0, 0.0));
  _trigeo.pushUv(glm::vec2(0.0f, 0.0f));
  _trigeo.pushUv(glm::vec2(1.0f, 0.0f));
  _trigeo.pushUv(glm::vec2(0.0f, 1.0f));
  _trigeo.build();
}

void  Loader::drawParticules(gdl::AShader &shader, glm::mat4 trans)
{
  _trigeo.draw(shader, trans, GL_TRIANGLES);
}

void  Loader::pushTexture(gdl::Geometry *geometry)
{
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
}

void Loader::drawGeometry(gdl::AShader &shader, glm::mat4 trans)
{
	_geometry.draw(shader, trans, GL_QUADS);
}

void 	Loader::bindTexture(type texttype)
{
  if (texttype < NOTHING && texttype >= BORDER)
  	_textures[texttype]->bind();
}
