#include "StaticShader.h"

const char* StaticShader::_VERTEX_FILE = "vert.vs";
const char* StaticShader::_FRAGMENT_FILE = "frag.fs";


StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	ShaderProgram::bindAttribute(0, "vPosition");
	ShaderProgram::bindAttribute(1, "vColor");
	ShaderProgram::bindAttribute(2, "vTexCoords");
	ShaderProgram::bindAttribute(3, "vNormal");
}

void StaticShader::getAllUniformLocations()
{
	_location_MVP = ShaderProgram::getUniformLocation("MVP");
	_location_transformMatrix = ShaderProgram::getUniformLocation("transformMatrix");
	_location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	_location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	_location_lightPosition = ShaderProgram::getUniformLocation("lightPosition");
	_location_lightColor = ShaderProgram::getUniformLocation("lightColor");
	_location_shineDamper = ShaderProgram::getUniformLocation("shineDamper");
	_location_reflectivity = ShaderProgram::getUniformLocation("reflectivity");
	_location_plane = ShaderProgram::getUniformLocation("plane");
}

void StaticShader::loadTransformMatrix(glm::mat4 &p_matrix)
{
	ShaderProgram::loadMatrix(_location_transformMatrix, p_matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 &p_matrix)
{
	ShaderProgram::loadMatrix(_location_projectionMatrix, p_matrix);
}

void StaticShader::loadViewMatrix(Camera &p_camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(p_camera);
	ShaderProgram::loadMatrix(_location_viewMatrix, viewMatrix);
}

void StaticShader::loadLight(Light &p_light)
{
	ShaderProgram::loadVector(_location_lightPosition, p_light.getPostion());
	ShaderProgram::loadVector(_location_lightColor, p_light.getColor());
}

void StaticShader::loadShineVariables(float p_damper, float p_reflectivity)
{
	ShaderProgram::loadFloat(_location_shineDamper, p_damper);
	ShaderProgram::loadFloat(_location_reflectivity, p_reflectivity);
}

void StaticShader::loadClipPlane(glm::fvec4 p_plane)
{
	loadVector(_location_plane, p_plane);
}

void StaticShader::loadMVP(glm::mat4 &p_matrix)
{
	ShaderProgram::loadMatrix(_location_MVP, p_matrix);
}