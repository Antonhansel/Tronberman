/*
** Joystick.hpp for Joystick in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  15 14:59:16 2014 Antonin Ribeaud
** Last update Thu May  15 14:59:16 2014 Antonin Ribeaud
*/

#ifndef _JOYSTICK_HPP_
# define _JOYSTICK_HPP_

# include <fcntl.h>
# include <unistd.h>
# include <string>
# include <linux/joystick.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include "AObject.hpp"

class Joystick {
protected:
    int             _fd;
    bool            _connected;
    struct js_event _e;
    std::string     _name;
    bool             _joyevent;
    key             _lastEvent;
    int             _vert;
    int             _hor;
    double          _time;
    SDL_Joystick    *_stick;
    SDL_Event        _event;
public:
    Joystick(const std::string &path);
    ~Joystick();
    std::string getName() const;
    key         update(gdl::Clock const &clock);
    bool        getStatus() const;
    key         mapJoystick();
};

#endif /*_JOYSTICK_HPP_*/