#ifndef _AOBJECT_HPP_
# define _AOBJECT_HPP_

# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <Model.hh> 
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>

class AObject
{
public:
	AObject();
	virtual ~AObject();
	virtual bool 	initialize() = 0;
	virtual void 	update(gdl::Clock const &clock, gdl::Input &input) = 0;
	virtual void 	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
	void 			translate(glm::vec3 const &v);
	void 			rotate(glm::vec3 const& axis, float angle);
	void 			scale(glm::vec3 const& scale);
	void			setPos(float, float);
	glm::mat4 		getTransformation();
protected:
	float		_trans;
	float		_posx;
	float		_posy;
	glm::vec3	_position;
	glm::vec3	_rotation;
	glm::vec3	_scale;
};

#endif /*!_AOBJECT_HPP_*/