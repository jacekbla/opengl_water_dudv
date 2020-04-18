#include "Maths.h"



Maths::Maths()
{
}


Maths::~Maths()
{
}


glm::mat4 Maths::createTransformMatrix(glm::vec3 p_translation, float p_rotX, float p_rotY, float p_rotZ, float p_scale)
{
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), p_translation);
	glm::mat4 RtX = glm::rotate(Tr, glm::radians(p_rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 RtY = glm::rotate(RtX, glm::radians(p_rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 RtZ = glm::rotate(RtY, glm::radians(p_rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Scale = glm::scale(RtZ, glm::vec3(p_scale, p_scale, p_scale));

	return Scale;
}

glm::mat4 Maths::createViewMatrix(Camera p_camera)
{
	glm::mat4 viewMatrix(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(p_camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(p_camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 cameraPos = p_camera.getPosition();
	glm::vec3 negativeCameraPos(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);
	return viewMatrix;
}

glm::mat4 Maths::createMVP()
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 Rt = glm::rotate(glm::mat4(1.0f), glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	return Projection * Tr * Rt;
}