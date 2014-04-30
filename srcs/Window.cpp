/*
** Window.cpp for Window in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 19:12:38 2014 Antonin Ribeaud
** Last update Mon Apr  28 19:12:38 2014 Antonin Ribeaud
*/

#include "Window.hpp"

Window::Window()
{
	start(100, 100, "test");
}

Window::~Window()
{

}
bool Window::start(unsigned int swidth, unsigned int sheight, const std::string &name)
{}
void Window::updateInputs(gdl::Input &input) const
{}
void Window::updateClock(gdl::Clock &clock) const
{}
void Window::flush() const
{}
void Window::stop() const
{}
