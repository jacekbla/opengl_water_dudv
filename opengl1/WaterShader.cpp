#include "WaterShader.h"

const char* WaterShader::_VERTEX_FILE = "waterVert.vs";
const char* WaterShader::_FRAGMENT_FILE = "waterFrag.fs";

WaterShader::~WaterShader()
{
}

void WaterShader::bindAttributes()
{
	ShaderProgram::bindAttribute(0, "vPosition");
}

void WaterShader::getAllUniformLocations()
{
	_location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	_location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	_location_modelMatrix = ShaderProgram::getUniformLocation("modelMatrix");
	_location_reflectionTexture = ShaderProgram::getUniformLocation("reflectionTexture");
	_location_refractionTexture = ShaderProgram::getUniformLocation("refractionTexture");
	_location_dudvMap = ShaderProgram::getUniformLocation("dudvMap");
	_location_moveFactor = ShaderProgram::getUniformLocation("moveFactor");
	_location_cameraPosition = ShaderProgram::getUniformLocation("cameraPosition");
	_location_depthMap = ShaderProgram::getUniformLocation("depthMap");
}

void WaterShader::connectTextureUnits()
{
	ShaderProgram::loadInt(_location_reflectionTexture, 0);
	ShaderProgram::loadInt(_location_refractionTexture, 1);
	ShaderProgram::loadInt(_location_dudvMap, 2);
	ShaderProgram::loadInt(_location_depthMap, 3);
}

void WaterShader::loadProjectionMatrix(glm::mat4 &p_matrix)
{
	ShaderProgram::loadMatrix(_location_projectionMatrix, p_matrix);
}

void WaterShader::loadViewMatrix(Camera &p_camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(p_camera);
	ShaderProgram::loadMatrix(_location_viewMatrix, viewMatrix);
	glm::vec3 pos = p_camera.getPosition();
	ShaderProgram::loadVector(_location_cameraPosition, pos);
}

void WaterShader::loadModelMatrix(glm::mat4 &p_matrix)
{
	ShaderProgram::loadMatrix(_location_modelMatrix, p_matrix);
}

void WaterShader::loadMoveFactor(float p_factor)
{
	ShaderProgram::loadFloat(_location_moveFactor, p_factor);
}
