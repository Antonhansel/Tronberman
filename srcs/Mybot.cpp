#include "Mybot.hpp"

Mybot::Mybot()
{
  _map = NULL;
}

Mybot::~Mybot()
{
	
}

bool  Mybot::checkMove(float y, float x)
{
  std::pair<float, float>   pos1;
  std::pair<float, float>   pos2;
  std::pair<float, float>   pos3;
  std::pair<float, float>   pos4;
  AObject                   *obj1 = NULL;
  AObject                   *obj2 = NULL;
  AObject                   *obj3 = NULL;
  AObject                   *obj4 = NULL;
  bool                      error = true;

if (y < 0) 
  y -= 1;
if (x < 0)
  x -= 1;

  pos1 = std::make_pair((float)((int)(y)), (float)((int)(x)));
  pos2 = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x)));
  pos3 = std::make_pair((float)((int)(y)), (float)((int)(x + 0.9)));
  pos4 = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x + 0.9)));

  if ((*_map).find(pos1) != (*_map).end())
    obj1 = (*_map).find(pos1)->second;
  if ((*_map).find(pos2) != (*_map).end())
    obj2 = (*_map).find(pos2)->second;
  if ((*_map).find(pos3) != (*_map).end())
    obj3 = (*_map).find(pos3)->second;
  if ((*_map).find(pos4) != (*_map).end())
    obj4 = (*_map).find(pos4)->second;

  if (obj1 != NULL && (obj1->getType() == BLOCKD || obj1->getType() == BORDER))
    error = false;
  if (obj2 != NULL && (obj2->getType() == BLOCKD || obj2->getType() == BORDER))
    error = false;
  if (obj3 != NULL && (obj3->getType() == BLOCKD || obj3->getType() == BORDER))
    error = false;
  if (obj4 != NULL && (obj4->getType() == BLOCKD || obj4->getType() == BORDER))
    error = false;
  return (error);
}

void   Mybot::randomNbr()
{
  int   i;

  i = rand() % 100;
  if (i < 20)
    _up++;
  if (i >= 20 && i < 40)
    _left++;
  if (i >= 40 && i < 60)
    _right++;
  if (i >= 60 && i < 80)
    _down++;

  if (_up > _down && _up > _left && _up > _right)
    _direction = UP;
  else if (_left > _down && _left > _up && _left > _right)
    _direction = LEFT;
  else if (_down > _left && _down > _up && _down > _right)
    _direction = DOWN;
  else if (_right > _down && _right > _up && _right > _left)
    _direction = RIGHT;

  if (_down > 10 || _right > 10 || _up > 10 || _left > 10)
  {
    _down = 0;
    _left = 0;
    _up = 0;
    _right = 0;
  }
}

void Mybot::update(gdl::Clock const &clock, gdl::Input &input)
{
  _trans = static_cast<float>(clock.getElapsed()) * _speed / 2;

  randomNbr();
  if (_direction == UP && checkMove(_pos.first, _pos.second + (1 * _trans)) == true)
  {
      _pos.second += 1 * _trans;
      translate(glm::vec3(0, 0, 1) * _trans);
  }
  else if (_direction == LEFT && checkMove(_pos.first + (1 * _trans), _pos.second) == true)
  {
    _pos.first += 1 * _trans;
    translate(glm::vec3(1, 0, 0) * _trans);
  }
  else if (_direction == DOWN && checkMove(_pos.first, _pos.second + (-1 * _trans)) == true)
  {
     _pos.second += -1 * _trans;
     translate(glm::vec3(0, 0, -1) * _trans);
  }
  else if (_direction == RIGHT && checkMove(_pos.first + (-1 * _trans), _pos.second) == true)
  {
    _pos.first += -1 * _trans;
    translate(glm::vec3(-1, 0, 0) * _trans); 
  }
}

void Mybot::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Mybot::initialize()
{
  _speed = 10.0f;
  if (_texture.load("./ressources/assets/face.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
	
  _geometry.setColor(glm::vec4(1, 1, 0, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.setColor(glm::vec4(1, 0, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.setColor(glm::vec4(0, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.setColor(glm::vec4(1, 0, 0, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  return (true);
}