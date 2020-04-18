#include "Renderer.h"

const float Renderer::_FOV = 90.0f;
const float Renderer::_NEAR_PLANE = 0.1f;
const float Renderer::_FAR_PLANE = 1000.0f;

Renderer::Renderer(StaticShader p_shader)
{
	_shader = p_shader;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	createProjectionMatrix();
	p_shader.start();
	p_shader.loadProjectionMatrix(_projectionMatrix);
	p_shader.stop();
}

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(std::map<TexturedModel, std::vector<Entity>> p_entities)
{
	for (std::map<TexturedModel, std::vector<Entity>>::value_type& val : p_entities)
	{
		TexturedModel model = val.first;
		prepareTexturedModel(model);
		std::vector<Entity> batch = val.second;
		for (Entity e : batch)
		{
			prepareInstance(e);
			glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void Renderer::renderRaw(RawModel p_model)
{
	glFuncs::ref().glBindVertexArray(p_model.getVaoID());
	glFuncs::ref().glEnableVertexAttribArray(0);
	glFuncs::ref().glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, p_model.getVertexCount(), GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
	glutPostRedisplay();

	glFuncs::ref().glDisableVertexAttribArray(0);
	glFuncs::ref().glBindVertexArray(0);
}

void Renderer::renderTextured(TexturedModel p_texturedModel)
{
	RawModel model = p_texturedModel.getRawModel();
	glFuncs::ref().glBindVertexArray(model.getVaoID());
	glFuncs::ref().glEnableVertexAttribArray(0);
	glFuncs::ref().glEnableVertexAttribArray(1);
	glFuncs::ref().glEnableVertexAttribArray(2);
	glFuncs::ref().glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, p_texturedModel.getTexture().getTextureID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
	glutPostRedisplay();

	glFuncs::ref().glDisableVertexAttribArray(0);
	glFuncs::ref().glDisableVertexAttribArray(1);
	glFuncs::ref().glDisableVertexAttribArray(2);
	glFuncs::ref().glBindVertexArray(0);
}

void Renderer::renderEntity(Entity p_entity, StaticShader p_shader)
{
	TexturedModel model = p_entity.getModel();
	RawModel rawModel = model.getRawModel();
	glFuncs::ref().glBindVertexArray(rawModel.getVaoID());
	glFuncs::ref().glEnableVertexAttribArray(0);
	glFuncs::ref().glEnableVertexAttribArray(1);
	glFuncs::ref().glEnableVertexAttribArray(2);
	glFuncs::ref().glEnableVertexAttribArray(3);

	glm::mat4 transformMatrix = Maths::createTransformMatrix(p_entity.getPosition(), p_entity.getRotX(), p_entity.getRotY(), p_entity.getRotZ(), p_entity.getScale());
	glm::mat4 MVPMatrix = Maths::createMVP();

	p_shader.loadTransformMatrix(transformMatrix);
	p_shader.loadMVP(MVPMatrix);
	ModelTexture texture = model.getTexture();
	p_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());

	glFuncs::ref().glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getTextureID());
	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
	glutPostRedisplay();

	glFuncs::ref().glDisableVertexAttribArray(0);
	glFuncs::ref().glDisableVertexAttribArray(1);
	glFuncs::ref().glDisableVertexAttribArray(2);
	glFuncs::ref().glDisableVertexAttribArray(3);
	glFuncs::ref().glBindVertexArray(0);
}

glm::mat4 Renderer::getProjectionMatrix() const
{
	return _projectionMatrix;
}

void Renderer::createProjectionMatrix()
{
	float aspectRatio = (float)DisplayManager::getWIDTH() / (float)DisplayManager::getHEIGHT();
	float y_scale = (float)((1.0f / tan(glm::radians(_FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = _FAR_PLANE - _NEAR_PLANE;

	_projectionMatrix = glm::mat4(1.0f);
	_projectionMatrix[0][0] = x_scale;
	_projectionMatrix[1][1] = y_scale;
	_projectionMatrix[2][2] = -((_FAR_PLANE + _NEAR_PLANE) / frustum_length);
	_projectionMatrix[2][3] = -1.0f;
	_projectionMatrix[3][2] = -((2.0f * _NEAR_PLANE * _FAR_PLANE) / frustum_length);
	_projectionMatrix[3][3] = 0.0f;
}

void Renderer::prepareTexturedModel(TexturedModel p_model)
{
	RawModel rawModel = p_model.getRawModel();
	glFuncs::ref().glBindVertexArray(rawModel.getVaoID());
	glFuncs::ref().glEnableVertexAttribArray(0);
	glFuncs::ref().glEnableVertexAttribArray(1);
	glFuncs::ref().glEnableVertexAttribArray(2);
	glFuncs::ref().glEnableVertexAttribArray(3);

	ModelTexture texture = p_model.getTexture();
	_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());

	glFuncs::ref().glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, p_model.getTexture().getTextureID());
}

void Renderer::unbindTexturedModel()
{
	glFuncs::ref().glDisableVertexAttribArray(0);
	glFuncs::ref().glDisableVertexAttribArray(1);
	glFuncs::ref().glDisableVertexAttribArray(2);
	glFuncs::ref().glDisableVertexAttribArray(3);
	glFuncs::ref().glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity p_entity)
{
	glm::mat4 transformMatrix = Maths::createTransformMatrix(p_entity.getPosition(), p_entity.getRotX(), p_entity.getRotY(), p_entity.getRotZ(), p_entity.getScale());
	glm::mat4 MVPMatrix = Maths::createMVP();
	_shader.loadTransformMatrix(transformMatrix);
	_shader.loadMVP(MVPMatrix);
}
