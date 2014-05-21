/*
** Preview.cpp for Preview in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:02 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:02 2014 Antonin Ribeaud
*/

#include "Preview.hpp"

Preview::Preview(Camera *camera, Loader *loader)
{
	_camera = camera;
	_loader = loader;
	_angle = 0;
	_posy = 20;
	_posx = 0;
	_posz = -30;
}

Preview::~Preview()
{
}

bool		Preview::initialize()
{
	std::vector<std::string> paths;

	paths.push_back("./ressources/maps/yolo.xml");
	_saving = new Saving(paths);
	_maps = _saving->getListMap();
	std::cout << "PREVIEW STARTED" << std::endl;
	_xend = _maps.back()->getSize()/2;
	return (true);
}

bool		Preview::update(gdl::Clock const &clock, gdl::Input &input)
{
	return (true);
}

void 		Preview::setCameraAngle()
{
  // _angle = _angle + 0.2;
  // if (_angle > 360)
  //   _angle = 0;
	_angle = 75;
  _posx = cos((_angle/180) * PI) * 30 + _xend;
  _posz = sin((_angle/180) * PI) * 30 + _xend;
  _camera->moveCamera(vec3(_posx + _xend, _posy, _posz - _xend/8), vec3(_xend, 0,_xend), vec3(0,1,0), 3);
}

void		Preview::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  type LastType = static_cast<type>(-1);
  AObject     *tmp;
  Map 			*_map = _maps.back();

  	_camera->previewMode(true);
	setCameraAngle();
	for (int x = 0; x < _map->getSize(); ++x)
  	{
	    for (int y = 0; y < _map->getSize(); ++y)
	    {
		  tmp = _map->getCase(x, y);
		   	if (!tmp)
		        continue;
		  if (tmp->getType() != LastType)
		      {
		        LastType = tmp->getType();
		        _loader->bindTexture(LastType);
		      }
		   _loader->drawGeometry(shader, tmp->getTransformation());
		}
	}
  _camera->previewMode(false);
}
