/*
** Char.cpp for char in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 21:11:55 2014 Antonin Ribeaud
** Last update Tue Apr  29 21:11:55 2014 Antonin Ribeaud
*/

#include "Char.hpp"
#include <iostream>

Char::Char(int players, int screen, std::map< std::pair<int, int>, Case *> map)
{
	std::string model;

	model = "./ressources/assets/marvin.fbx";
	_players = players;
	_screen = screen;
	_map = map;
	_model = new gdl::Model;
	_model->gdl::Model::load(model);
}

Char::~Char()
{
}

float	Char::getTrans()
{
	return (_trans);
}

int 	Char::convertToInt(float nb)
{
	int	nb1;

	nb1 = (int(nb * 10)) % 10;
	if (nb < 0)
	{
		if (nb1 < 5)
			return (ceil(nb));
		else
			return (floor(nb));
	}
	else
	{
		if (nb1 < 5)
			return (floor(nb));
		else
			return (ceil(nb1));
	}
}

void Char::update(gdl::Clock const &clock, gdl::Input &input)
{
	std::pair<int, int>	pos;

	_trans = static_cast<float>(clock.getElapsed()) * _speed;
	if (_screen == 1)
	{
		glm::vec3 _posTmp = _position;
		if (input.getKey(SDLK_UP))
		{
			_posTmp = _position + glm::vec3(0, 0, 1) * _trans;
			std::cout << "current posx = " << _position.x << " && posy = " << _position.z << std::endl;
			std::cout << "----- >   wanted posx = " << _posTmp.x << " && posy = " << _posTmp.z << std::endl;
			pos = std::make_pair((convertToInt(_posTmp.x)), (convertToInt(_posTmp.z + 0.5)));
			std::cout << "----- >   test wanted posx = " << pos.first << " && posy = " << pos.second << std::endl;
			if (_map[pos] == NULL)
			{
				translate(glm::vec3(0, 0, 1) * _trans);
			}
			else
				_trans = 0;
		}
		if (input.getKey(SDLK_DOWN))
		{
			_posTmp = _position + glm::vec3(0, 0, -1) * _trans;
			pos = std::make_pair((convertToInt(_posTmp.x)), (convertToInt(_posTmp.z + 0.5)));
			//std::cout << "posx = " << _posTmp.x << " && posy = " << _posTmp.z << " && trans " << _trans << std::endl;
			if (_map[pos] == NULL)
			{
				translate(glm::vec3(0, 0, -1) * _trans);
			}
			else
				_trans = 0;
		}
		if (input.getKey(SDLK_LEFT))
		{
			_posTmp = _position + glm::vec3(1, 0, 0) * _trans;
			pos = std::make_pair((convertToInt(_posTmp.x + 0.5)), (convertToInt(_posTmp.z)));
			//std::cout << "posx = " << _posTmp.x << " && posy = " << _posTmp.z << " && trans " << _trans << std::endl;

			if (_map[pos] == NULL)
				translate(glm::vec3(1, 0, 0) * _trans);
			else
				_trans = 0;

		}
		if (input.getKey(SDLK_RIGHT))
		{
			_posTmp = _position + glm::vec3(-1, 0, 0) * _trans;
			pos = std::make_pair((convertToInt(_posTmp.x - 0.5)), (convertToInt(_posTmp.z)));
			//std::cout << "posx = " << _posTmp.x << " && posy = " << _posTmp.z << " && trans " << _trans << std::endl;
			if (_map[pos] == NULL)
				translate(glm::vec3(-1, 0, 0) * _trans);
			else
				_trans = 0;
		}
	}
	else
	{
		if (input.getKey(SDLK_z))
		translate(glm::vec3(0, 0, 1) * _trans);
		if (input.getKey(SDLK_s))
			translate(glm::vec3(0, 0, -1) * _trans);
		if (input.getKey(SDLK_q))
			translate(glm::vec3(1, 0, 0) * _trans);
		if (input.getKey(SDLK_d))
			translate(glm::vec3(-1, 0, 0) * _trans);		
	}
  	//_model->gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
	//_model->gdl::Model::update(clock.getElapsed());
}

void Char::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
	//gdl::Model::Begin();
 	//glPushMatrix();
 	//_model->gdl::Model::play("Take 001");
  	//glTranslatef(this->position_->x, 0.0f, this->position_->y);
  	//glRotatef(this->rotation_->x, 0.0f, 0.0f, 0.0f);
  	//_model->gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  	//glPopMatrix();
	// 	gdl::Model::End();
}

bool	Char::initialize()
{
	_speed = 10.0f;
	if (_texture.load("./ressources/assets/char.tga") == false)
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

	//_geometry.setColor(glm::vec4(1, 1, 0, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	//_geometry.setColor(glm::vec4(0, 1, 1, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	//_geometry.setColor(glm::vec4(1, 0, 1, 1));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	//_geometry.setColor(glm::vec4(0, 1, 0, 1));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	//_geometry.setColor(glm::vec4(0, 0, 1, 1));
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