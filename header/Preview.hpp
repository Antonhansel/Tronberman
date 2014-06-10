/*
** Preview.hpp for Preview in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:42 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:42 2014 Antonin Ribeaud
*/

#ifndef _PREVIEW_HPP_
# define _PREVIEW_HPP_

// # include "Camera.hpp"
// # include "Loader.hpp"
//# include "Map.hpp"
# include "Saving.hpp"
# include "Text.hpp"

#define PI 3.14159

class Preview
{
public:
	Preview(Camera *, Loader *);
	~Preview();
	bool					initialize();
	bool					initializeSave();
	bool					update(gdl::Clock const &, gdl::Input &, const bool);
	void					draw(gdl::AShader &, gdl::Clock const &);
	void 					setCameraAngle();
	void 					getPaths(const char *);
	bool 					checkName(const char *);
	std::string				makePath(const char *, const char *);
	void 					changeMap(const int);
	void 					changeMapSave(const int);
	Map 					*getMap() const;
	Saving 					*getInstance() const;
	bool					getState() const;
	void					setState(const bool);
	bool					getResult() const;
	void					resetText();

private:
	std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > _big;
	std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > _nb;
	double 											_time;
	std::vector<Map*>::iterator 					_it;
	std::vector<std::vector<Player *> >::iterator	_itPlayer;
	Map 											*_map;
	std::vector<std::string> 						_paths;
	Camera 											*_camera;
	Loader 											*_loader;
	std::vector<Map*> 								*_maps;
	std::vector< std::vector<Player *> > 			*_players;
	float											_angle;
  	float											_posy;
  	float											_posz;
  	float											_posx;
  	float											_xend;
  	std::vector<Saving *>							_save;
  	bool											_state;
  	bool											_result;
  	Text 											*_text;
  	std::string 									_nbSize;
  	std::string 									_nbPlayer;
};

#endif /*!_PREVIEW_HPP_*/
