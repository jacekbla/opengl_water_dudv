#include "Utility.h"

#ifndef LIGHT_H
#define LIGHT_H


class Light
{
public:
	Light(glm::vec3 p_position, glm::vec3 p_color) : _position(p_position), _color(p_color) {};
	~Light();

	glm::vec3 &getPostion();
	glm::vec3 &getColor();
	void setPostion(glm::vec3 p_position);
	void setColor(glm::vec3 p_color);

private:
	glm::vec3 _position;
	glm::vec3 _color;
};


#endif LIGHT_H