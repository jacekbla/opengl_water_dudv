#include "Utility.h"
#include "Camera.h"

#ifndef MATHS_H
#define MATHS_H

class Maths
{
public:
	Maths();
	~Maths();

	static glm::mat4 createTransformMatrix(glm::vec3 p_translation, float p_rotX, float p_rotY, float p_rotZ, float p_scale);
	static glm::mat4 createViewMatrix(Camera p_camera);
	static glm::mat4 createMVP();
};


#endif MATHS_H