/*
** Joystick.cpp for Joystick in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  15 14:58:34 2014 Antonin Ribeaud
** Last update Thu May  15 14:58:34 2014 Antonin Ribeaud
*/

#include "Joystick.hpp"

Joystick::Joystick(const std::string &path)
{
	char 	name[256];

	if ((_fd = open(path.c_str(), O_NONBLOCK)) > 0)
	{
		ioctl(_fd, JSIOCGNAME(256), name);
		_connected = true;
		_name = name;
		std::cout <<_name << std::endl;
		if (_name.find("Sony") != _name.npos)
		{
			_vert = 0;
			_hor = 1;
		}
		else if (_name.find("Microsoft") != _name.npos)
		{
			std::cout << "XBOX" << std::endl;
			_vert = 0;
			_hor = 1;
		}
	}
	else
		_connected = false;
	_joyevent = false;
	_time = 0;
}

Joystick::~Joystick()
{

}

key 		Joystick::mapJoystick()
{
	if (_time > 0.02 || _joyevent == false)
	{
	if (_e.type &= JS_EVENT_AXIS)
	{
		_time = 0;
	if (_e.number == _vert)
	{
		std::cout << _e.value << std::endl;
		if (_e.value > 32000)
		{
		_joyevent = true;
		_lastEvent = PRIGHT;
		return (PRIGHT);
		}
		else if (_e.value < -32000)
		{
		_joyevent = true;
		_lastEvent = PLEFT;
		return (PLEFT);
		}
		else 
		_joyevent = false;
	}
	}
	else
		_joyevent = false;
	}
	return (_lastEvent);
}

key			Joystick::update(gdl::Clock const &clock)
{
	_time += clock.getElapsed();
	while (read(_fd, &_e, sizeof(struct js_event)) > 0)
	{
		return (mapJoystick());
	}
	if (_joyevent == false)
		_lastEvent = NONE;
	return (_lastEvent);
}

std::string Joystick::getName() const
{
	return (_name);
}

bool 		Joystick::getStatus() const
{
	return (_connected);
}

// Joystick::Joystick(const std::string &path)
// {
// 	// _file.open(path.c_str(), std::ios::binary);
// 	// if (_file.good())
// 	// 	_connected = true;
// 	// else
// 	// 	_connected = false;
// 	//_file.read((char*)&_e, sizeof(_e));
// }

// void 		Joystick::update()
// {
// 	//std::string test;
//     //int retval;
// 	// if (!_file.good())
// 	// 	_connected = false;
// 	// if (_connected == true)
// 	// {
// 		//TEST 1
// 		// if (_file.getline((char*)&_e, sizeof(_e)))
// 		// 	std::cout << _e.number << std::endl;
// 		//TEST 2
// 		// FD_ZERO(&rfds);
//   		// FD_SET(_fd, &rfds);
//   		// retval = select(1, &rfds, NULL, NULL, &tv);
// 		// if (ret > 0)
// 		//TEST 3
// 		//std::cout << "TO READ" << _file.rdbuf()->in_avail() << std::endl;
// 		// if ((unsigned int)sizeof(_e) <= _file.rdbuf()->in_avail())
// 		// {
//   		// _file.read((char*)&_e, sizeof(_e));
//   		//  printf("%d\t%d\t%d\t%d\n", _e.time, _e.value, _e.type, _e.number);
//   		// }
//   		//TEST 4
//     	// _file.getline((char*)&_e, sizeof(_e));
//     	//std::cout << "SIZE: " << i << std::endl;
//     	//TEST 5
//   		// if ((unsigned int)_file.readsome((char*)&_e, sizeof(_e)) >= sizeof(_e))
// 		// {
// 		// 	//TEST 1
// 		// 	//_file.seekg(_file.beg);
// 		// 	//TEST 2
// 		// 	_file.sync();
//   		// _file.ignore(sizeof(_e));
//   		// printf("%d\t%d\t%d\t%d\n", _e.time, _e.value, _e.type, _e.number);
// 		// }
// 		//while ((unsigned int)_file.readsome((char*)&_e, sizeof(_e)) > 0)
// 		//{
// 			//TEST 1
// 			//_file.seekg(_file.end);
// 			//TEST 1.2
// 			//_file.seekg(_file.beg);
// 			//TEST 2
// 			//_file.sync();	
//   			//_file.ignore(sizeof(_e));
//   			//printf("%d\t%d\t%d\t%d\n", _e.time, _e.value, _e.type, _e.number);
// 		//}
// 	//}
// 	//if (_e.type &= JS_EVENT_BUTTON)
// 	//std::cout << "INPUT" << _e.number << std::endl;
// }