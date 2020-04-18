#include "Camera.h"

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition() const
{
	return _position;
}

float Camera::getPitch() const
{
	return _pitch;
}

float Camera::getYaw() const
{
	return _yaw;
}

float Camera::getRoll() const
{
	return _roll;
}

void Camera::setPosition(glm::vec3 p_position)
{
	_position = p_position;
}

void Camera::invertPitch()
{
	_pitch = -_pitch;
}

void Camera::move()
{
	if (GetKeyState('W') & 0x8000)
	{
		float xStep = _MOVE_SENSITIVITY * sin(glm::radians(_yaw));
		float zStep = _MOVE_SENSITIVITY * cos(glm::radians(_yaw));

		_position.x += xStep;
		_position.z -= zStep;
	}
	if (GetKeyState('D') & 0x8000)
	{
		float xStep = _MOVE_SENSITIVITY * cos(glm::radians(_yaw));
		float zStep = _MOVE_SENSITIVITY * sin(glm::radians(_yaw));

		_position.x += xStep;
		_position.z += zStep;
	}
	if (GetKeyState('A') & 0x8000)
	{
		float xStep = _MOVE_SENSITIVITY * cos(glm::radians(_yaw));
		float zStep = _MOVE_SENSITIVITY * sin(glm::radians(_yaw));

		_position.x -= xStep;
		_position.z -= zStep;
	}
	if (GetKeyState('S') & 0x8000)
	{
		float xStep = _MOVE_SENSITIVITY * sin(glm::radians(_yaw));
		float zStep = _MOVE_SENSITIVITY * cos(glm::radians(_yaw));

		_position.x -= xStep;
		_position.z += zStep;
	}
	if (GetKeyState(' ') & 0x8000)
	{
		_position.y += _MOVE_SENSITIVITY;
	}
	if (GetKeyState('C') & 0x8000)
	{
		_position.y -= _MOVE_SENSITIVITY;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		_pitch += _KEYBOARD_ANGLE_SENSITIVITY;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		_pitch -= _KEYBOARD_ANGLE_SENSITIVITY;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		_yaw -= _KEYBOARD_ANGLE_SENSITIVITY;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		_yaw += _KEYBOARD_ANGLE_SENSITIVITY;
	}

	POINT mousePos;
	GetCursorPos(&mousePos);
	if (GetKeyState(VK_RBUTTON) & 0x100)
	{
		if (GetKeyState(VK_LBUTTON) & 0x100)
		{
			float xStep = _MOVE_SENSITIVITY * sin(glm::radians(_yaw));
			float zStep = _MOVE_SENSITIVITY * cos(glm::radians(_yaw));

			_position.x += xStep;
			_position.z -= zStep;
		}

		int diffX = mousePos.x - _currMouseX;
		int diffY = mousePos.y - _currMouseY;
		if (diffX != 0 || diffY != 0)
		{
			_yaw += diffX * _MOUSE_ANGLE_SENSITIVITY;
			_pitch += diffY * _MOUSE_ANGLE_SENSITIVITY;
		}
	}
	_currMouseX = mousePos.x;
	_currMouseY = mousePos.y;
}