#include "Utility.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	explicit Camera()
	{ };
	~Camera();

	glm::vec3 getPosition() const;
	float getPitch() const;
	float getYaw() const;
	float getRoll() const;
	void setPosition(glm::vec3 p_position);

	void invertPitch();
	void move();

private:
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	float _pitch = 2.0f;
	float _yaw = 0.0f;
	float _roll = 0.0f;

	const float _MOUSE_ANGLE_SENSITIVITY = 0.15f;
	const float _KEYBOARD_ANGLE_SENSITIVITY = 0.4f;
	const float _MOVE_SENSITIVITY = 0.1f;

	int _currMouseX;
	int _currMouseY;
};


#endif CAMERA_H