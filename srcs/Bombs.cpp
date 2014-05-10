#include "Bombs.hpp"

Bombs::Bombs()
{
  initialize();
}

Bombs::~Bombs()
{}

void Bombs::update(gdl::Clock const &clock, gdl::Input &input)
{
  // if (input.getKey(SDLK_UP))
  //  translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
  // if (input.getKey(SDLK_DOWN))
  //  translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
  // if (input.getKey(SDLK_LEFT))
  //  translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  // if (input.getKey(SDLK_RIGHT))
  //  translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void  Bombs::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Bombs::initialize()
{
	 _speed = 10.0f;
  if (_texture.load("./ressources/assets/block.tga") == false)
    {
      std::cerr << "Cannot load the bombs texture" << std::endl;
      return (false);
    }

  return (true);
}