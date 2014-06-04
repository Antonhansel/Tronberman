/*
** AObject.hpp for AObject in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  29 11:50:59 2014 Antonin Ribeaud
** Last update Thu May  29 11:50:59 2014 Antonin Ribeaud
*/

#ifndef _AOBJECT_HPP_
# define _AOBJECT_HPP_

# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <Model.hh>
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>

class ParticleEngine;
class Map;

enum type
  {
    BORDER = 0,
    BOMB = 1,
    BOT = 2,
    PLAYER = 3,
    LASER = 4,
    BLOCK = 5,
    BLOCKD = 6,
    UNSELECTED = 7,
    SELECTED = 8,
    BONUSV = 9,
    BONUSB = 10,
    BONUSR = 11,
    NOTHING = 12
  };

enum key
{
  NONE = 10,
  PUP,
  PDOWN,
  PRIGHT,
  PLEFT,
  PBOMB,
  MRETURN,
  MBACKSPACE,
  MUP,
  MLEFT,
  MDOWN,
  MRIGHT,
  ESCAPE,
  MZERO,
  MONE,
  MTWO,
  MTHREE,
  MFOUR,
  MFIVE,
  MSIX,
  MSEVEN,
  MHEIGHT,
  MNINE,
  MDOT,
  PSAVE,
  FPSOFF,
  FPSON,
  GPLUS,
  GMINUS,
  KP1,
  KP2,
  SPACE
};

class AObject
{
public:
  AObject();
  virtual ~AObject();
  virtual bool 	initialize() = 0;
  virtual void 	update(gdl::Clock const &clock, gdl::Input &input) = 0;
  virtual void 	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  std::pair<float, float>	getPos() const;
  void 			translate(glm::vec3 const &v);
  void 			rotate(glm::vec3 const& rotation);
  void 			scale(glm::vec3 const& scale);
  void      setPos(std::pair<float, float>&);
  void      setAbsPos(std::pair<float, float>&);
  void			setAbsPos(float, float);
  void			setType(type);
  glm::mat4 		getTransformation();
  type			getType() const;
  void  setParticle(ParticleEngine *particles);
  void  setTexture(gdl::Texture *);
protected:
  bool                    _transformationDirty;
  glm::mat4               _transformation;
  type                    _type;
  std::pair<float, float>	_pos;
  glm::vec3	              _position;
  glm::vec3	              _rotation;
  glm::vec3	              _scale;
  gdl::Texture            *_texture;
  ParticleEngine          *_particles;
};

#endif /*!_AOBJECT_HPP_*/
