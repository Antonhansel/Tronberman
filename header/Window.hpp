/*
** Window.hpp for epitech in /home/apollo/rendu/bestbomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 19:06:31 2014 Antonin Ribeaud
** Last update Mon Apr  28 19:06:31 2014 Antonin Ribeaud
*/

#ifndef _WINDOW_HPP_
# define _WINDOW_HPP_

# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <BasicShader.hh> 
# include <Model.hh>
# include <sstream>

class Window : public gdl::SdlContext
{
public:
	Window();
	~Window();
private:
	bool start(unsigned int swidth, unsigned int sheight, const std::string &name); 
	void updateInputs(gdl::Input &input) const; 
	void updateClock(gdl::Clock &clock) const; 
	void flush() const;
	void stop() const;
};

#endif /*!_WINDOW_HPP_*/