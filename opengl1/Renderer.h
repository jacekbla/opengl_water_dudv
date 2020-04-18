#include "Utility.h"
#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"
#include "DisplayManager.h"
#include <map>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	explicit Renderer(StaticShader p_shader);
	~Renderer();

	void prepare();
	void render(std::map<TexturedModel, std::vector<Entity>> p_entities);
	void renderRaw(RawModel p_model);
	void renderTextured(TexturedModel p_texturedModel);
	void renderEntity(Entity p_entity, StaticShader p_shader);

	glm::mat4 getProjectionMatrix() const;

private:
	static const float _FOV;
	static const float _NEAR_PLANE;
	static const float _FAR_PLANE;

	StaticShader _shader;
	glm::mat4 _projectionMatrix;

	void createProjectionMatrix();
	void prepareTexturedModel(TexturedModel p_model);
	void unbindTexturedModel();
	void prepareInstance(Entity p_entity);
};

#endif RENDERER_H