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
  lastBind = NOTHING;
}

Loader::~Loader()
{
  for (std::vector<gdl::Texture *>::iterator it = _textures.begin(); it != _textures.end(); ++it)
    delete (*it);
  for (std::vector<gdl::Model *>::iterator it = _models.begin(); it != _models.end(); ++it)
    delete (*it);
}

bool Loader::loadModels()
{
  _models.resize(5, NULL);
  _models[1] = new gdl::Model();
  _models[2] = new gdl::Model();
  _models[3] = new gdl::Model();
  _models[4] = new gdl::Model();
  if (_models[1]->load( "./ressources/assets/anim/bomberman_white_run.FBX") == false
    || _models[2]->load("./ressources/assets/anim/bomberman_black_run.FBX") == false
    || _models[3]->load("./ressources/assets/anim/bomberman_blue_run.FBX") == false
    || _models[4]->load("./ressources/assets/anim/bomberman_gold_run.FBX") == false)
    {
        std::cout << "Error on loading model" << std::endl;
        return (false);
    }
  return (true);
}

bool  Loader::loadTextures()
{
  _textures.resize(12, NULL);
  _textures[BLOCKD] = new gdl::Texture();
  _textures[BONUSS] = new gdl::Texture();
  _textures[BORDER] = new gdl::Texture();
  _textures[BLOCK] = new gdl::Texture();
  _textures[BOMB] = new gdl::Texture();
  _textures[LASER] = new gdl::Texture();
  _textures[UNSELECTED] = new gdl::Texture();
  _textures[SELECTED] = new gdl::Texture();
  _textures[BONUSV] = new gdl::Texture();
  _textures[BONUSB] = new gdl::Texture();
  _textures[BONUSR] = new gdl::Texture();

  if (_textures[BLOCKD]->load("./ressources/assets/BLOCKD.tga") == false
    || _textures[BORDER]->load("./ressources/assets/BORDER.tga") == false
    || _textures[BLOCK]->load("./ressources/assets/BLOCK.tga") == false
    || _textures[BOMB]->load("./ressources/assets/BOMB.tga") == false
    || _textures[LASER]->load("./ressources/assets/LASER.tga") == false
    || _textures[UNSELECTED]->load("./ressources/fonts/blue.tga") == false 
    || _textures[SELECTED]->load("./ressources/fonts/red.tga") == false
    || _textures[BONUSV]->load("./ressources/assets/BONUS1.tga") == false
    || _textures[BONUSB]->load("./ressources/assets/BONUS2.tga") == false
    || _textures[BONUSR]->load("./ressources/assets/BONUS3.tga") == false
    || _textures[BONUSS]->load("./ressources/assets/BONUS4.tga") == false)
    return (false);
  return (true);
}

bool 	Loader::loadRessources()
{
  if (loadTextures() == false || loadModels() == false || initVertex() == false)
    return (false);
  loadParticules();
	return (true);
}

bool  Loader::initVertex()
{
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  pushTexture(&_geometry);

  _geometry.setColor(glm::vec4(1, 1, 0, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushTexture(&_geometry);

  _geometry.setColor(glm::vec4(1, 0, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  pushTexture(&_geometry);

  _geometry.setColor(glm::vec4(0, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushTexture(&_geometry);

  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  pushTexture(&_geometry);
  _geometry.build();
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

void  Loader::drawParticules(gdl::AShader &shader, glm::mat4 &trans)
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
  if (lastBind != texttype)
  	_textures[texttype]->bind();
}
