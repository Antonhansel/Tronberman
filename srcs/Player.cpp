//
// Player.cpp for Player in /home/chouag_m/rendu/bitbucker
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May 10 00:23:31 2014 Mehdi Chouag
// Last update Sat May 10 00:58:19 2014 Mehdi Chouag
//

#include "Player.hpp"
#include "Map.hpp"

Player::Player()
{
    _stock = 3;
    _range = 2;
    _x = 0;
    _life = 3;
}

Player::~Player()
{}

bool    Player::initialize()
{
    _speed = 7;
    _model.load( "./ressources/assets/bomberman_white_run.FBX");
    scale(glm::vec3(1,2,1));
    translate(glm::vec3(-0.5, 0, 0));
    return (true);
}

void	Player::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
    glPushMatrix();
    _model.setCurrentAnim(_anim);
    _model.gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
    glPopMatrix();
}

void    Player::setMap(Map *map)
{
    _map = map;
}

void    Player::setPlayer(int player)
{
    _player = player;
}

void    Player::setSpeed(float speed)
{
    _speed = speed;
}

bool	Player::checkMove(float x, float y)
{
    if (floor(_pos.first) == floor(_pos.first + x) && floor(_pos.second) == floor(_pos.second + y))
        return true;
    AObject *cas = _map->getCase(floor(_pos.first + x), floor(_pos.second + y));
    if (!cas)
        return (true);
    else if (cas->getType() == BONUS)
    {
        dynamic_cast<Bonus*>(cas)->addToPlayer(this);
        _map->deleteCube(floor(_pos.first + x), floor(_pos.second + y));  
        return (true);
    }
    else
        return (false);
}

void	Player::update(gdl::Clock const &clock, gdl::Input &input)
{
    float trans = static_cast<float>(clock.getElapsed()) * _speed;
    std::map<int, std::pair<float, float> > keymap;
    glm::vec3 rotation = glm::vec3(0);

    if (_player == 1)
    {
        keymap[SDLK_LEFT] = std::make_pair(trans, 0);
        keymap[SDLK_RIGHT] = std::make_pair(-trans, 0);
        keymap[SDLK_UP] = std::make_pair(0, trans);
        keymap[SDLK_DOWN] = std::make_pair(0, -trans);
    }
    else
    {
        keymap[SDLK_q] = std::make_pair(trans, 0);
        keymap[SDLK_d] = std::make_pair(-trans, 0);
        keymap[SDLK_z] = std::make_pair(0, trans);
        keymap[SDLK_s] = std::make_pair(0, -trans);
    }
    for (std::map<int, std::pair<float, float> >::iterator i = keymap.begin(); i != keymap.end(); ++i)
    {
        if (input.getKey(i->first))
        {
            if (checkMove(
                (float)i->second.first,
                (float)i->second.second)
                && checkMove(
                (float)i->second.first + 0.4,
                (float)i->second.second + 0.4)
                && checkMove(
                (float)i->second.first,
                (float)i->second.second + 0.4)
                && checkMove(
                (float)i->second.first + 0.4,
                (float)i->second.second)
                )
            {
                _pos.first += i->second.first;
                _pos.second += i->second.second;
                translate(glm::vec3(i->second.first, 0, i->second.second));
            }
            _anim = 2;
            rotation.y += (i->second.second) ? (SIGN(i->second.second) * 90 - 90) : (0);
            rotation.y += (i->second.first) ? (SIGN(i->second.first) * -90 + 180) : (0);
            rotate(rotation);
        }
    }
    if (_anim == 2)
        _anim = 1;
    else
        _anim = 0;
}

int  Player::getStock() const
{
    return (_stock);
}

void  Player::setStock(int stock)
{
    _stock = stock;
}

void  Player::setId(int id)
{
    _id = id;
}

int   Player::getId() const
{
    return (_id);
}

int   Player::getRange() const
{
    return (_range);
}

void  Player::setRange(int range)
{
    _range = range;
}

void    Player::setLife(int newLife)
{
    _life = newLife;
}

int     Player::getLife() const
{
    return (_life);
}