#include "Utility.h"
#include "TexturedModel.h"

#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
	Entity() :Entity(TexturedModel(), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f) {};
	Entity(TexturedModel p_model, glm::vec3 p_position, float p_rotX, float p_rotY, float p_rotZ, float p_scale) : 
		_model(p_model), _position(p_position), _rotX(p_rotX), _rotY(p_rotY), _rotZ(p_rotZ), _scale(p_scale) {};
	~Entity();

	TexturedModel getModel() const;
	glm::vec3 getPosition() const;
	float getRotX() const;
	float getRotY() const;
	float getRotZ() const;
	float getScale() const;
	void setModel(TexturedModel p_model);
	void setPosition(glm::vec3 p_position);
	void setRotX(float p_rotX);
	void setRotY(float p_rotY);
	void setRotZ(float p_rotZ);
	void setScale(float p_scale);

	void increasePosition(float p_dx, float p_dy, float p_dz);
	void increaseRotation(float p_dx, float p_dy, float p_dz);

private:
	TexturedModel _model;
	glm::vec3 _position;
	float _rotX, _rotY, _rotZ;
	float _scale;
};

#endif ENTITY_H