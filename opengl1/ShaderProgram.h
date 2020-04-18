#include "Utility.h"

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class ShaderProgram
{
public:
	explicit ShaderProgram(const char* p_vertexFile, const char* p_fragmentFile);
	~ShaderProgram();

	virtual void start();
	virtual void stop();
	virtual void cleanUp();

private:
	int _programHandle;
	int _vertexShaderHandle;
	int _fragmentShaderHandle;

	char* readShader(const char * p_shaderFile);
	void setShaders(const char* p_vertex, const char* p_pixel, int &p_programHandle, int &p_vertexShaderHandle, int &p_fragmentShaderHandle);
	void setShader(const char* p_file, int &p_programHandle, int &p_shaderHandle);

protected:
	virtual void bindAttributes();
	virtual void bindAttribute(int p_attribute, const char* p_variableName);
	virtual void getAllUniformLocations();
	int getUniformLocation(const char* p_uniformName);
	void loadInt(int p_location, int p_value);
	void loadFloat(int p_location, float p_value);
	void loadVector(int p_location, glm::vec3 &p_value);
	void loadVector(int p_location, glm::vec4 &p_value);
	void loadBoolean(int p_location, bool p_value);
	void loadMatrix(int p_location, glm::mat4 &p_matrix);
};

#endif SHADER_PROGRAM_H