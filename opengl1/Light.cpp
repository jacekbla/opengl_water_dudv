#include "Light.h"



Light::~Light()
{
}

glm::vec3 &Light::getPostion()
{
	return _position;
}

glm::vec3 &Light::getColor()
{
	return _color;
}

void Light::setPostion(glm::vec3 p_position)
{
	_position = p_position;
}

void Light::setColor(glm::vec3 p_color)
{
	_color = p_color;
}
