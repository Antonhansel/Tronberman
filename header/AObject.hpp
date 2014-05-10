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

enum type
  {
    BORDER = 0,
    BOMB = 1,
    BOT = 2,
    PLAYER = 3,
    LASER = 4,
    BLOCK = 5,
    BLOCKD = 6,
    BONUS = 7
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
  void 			rotate(glm::vec3 const& axis, float angle);
  void 			scale(glm::vec3 const& scale);
  void			setPos(std::pair<float, float>&);
  void			setType(type);
  glm::mat4 		getTransformation();
  type			getType() const;
  float			getTrans() const;
  void			setPlayer(int);
  void			setSpeed(float);
  void			setMap(std::map< std::pair<float, float>, AObject *> *);
  void      setBombs(std::map< std::pair<float, float>, AObject* >&);
  void      setIsAlive(bool);
  bool      getIsAlive() const;
  const std::map< std::pair<float, float>, AObject* >&  getBombs();

  /*TEST*/
  void  setTexture(gdl::Texture *);
protected:
  bool        _transformationDirty;
  glm::mat4   _transformation;
  float   _posx;
  float   _posy;
  type		_type;
  float		_trans;
  int 			_players;
  int 			_screen;
  std::pair<float, float>	_pos;
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  std::map< std::pair<float, float>, AObject *>	*_map;
  std::map< std::pair<float, float>, AObject* > _bombs;
  float		_speed;
  bool    _isAlive;
  gdl::Texture *_texture;
};

#endif /*!_AOBJECT_HPP_*/
