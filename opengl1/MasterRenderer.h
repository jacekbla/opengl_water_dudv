#include "Utility.h"
#include "StaticShader.h"
#include "Renderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include <map>

#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

class MasterRenderer
{
public:
	explicit MasterRenderer();
	~MasterRenderer();

	void cleanUp();
	void render(Light p_light, Camera p_camera, glm::fvec4 p_clipPlane);
	void processEntity(Entity p_entity);

	glm::mat4 getProjectionMatrix();

private:
	StaticShader _shader;
	Renderer *_renderer;

	std::map<TexturedModel, std::vector<Entity>> _entities;
};


#endif MASTER_RENDERER_H