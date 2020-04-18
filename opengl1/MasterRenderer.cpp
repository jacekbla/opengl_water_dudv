#include "MasterRenderer.h"



MasterRenderer::MasterRenderer()
{
	_renderer = new Renderer(_shader);
}


MasterRenderer::~MasterRenderer()
{
	delete _renderer;
}

void MasterRenderer::cleanUp()
{
	_shader.cleanUp();
}

void MasterRenderer::render(Light p_light, Camera p_camera, glm::fvec4 p_clipPlane)
{
	_renderer->prepare();
	_shader.start();
	_shader.loadClipPlane(p_clipPlane);
	_shader.loadLight(p_light);
	_shader.loadViewMatrix(p_camera);
	_renderer->render(_entities);
	_shader.stop();
	_entities.clear();
}

void MasterRenderer::processEntity(Entity p_entity)
{
	TexturedModel entityModel = p_entity.getModel();
	std::vector<Entity> batch = _entities[entityModel];
	if (!batch.empty())
	{
		batch.push_back(p_entity);
	}
	else
	{
		std::vector<Entity> newBatch;
		newBatch.push_back(p_entity);
		_entities.insert(std::pair<TexturedModel, std::vector<Entity>>(entityModel, newBatch));
	}
}

glm::mat4 MasterRenderer::getProjectionMatrix()
{
	return _renderer->getProjectionMatrix();
}
