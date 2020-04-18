#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(const char* p_vertexFile, const char* p_fragmentFile)
{
	setShaders(p_vertexFile, p_fragmentFile, _programHandle, _vertexShaderHandle, _fragmentShaderHandle);

	bindAttributes();
	getAllUniformLocations();
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::start()
{
	glFuncs::ref().glUseProgram(_programHandle);
}

void ShaderProgram::stop()
{
	glFuncs::ref().glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();
	glFuncs::ref().glDetachShader(_programHandle, _vertexShaderHandle);
	glFuncs::ref().glDetachShader(_programHandle, _fragmentShaderHandle);
	glFuncs::ref().glDeleteShader(_vertexShaderHandle);
	glFuncs::ref().glDeleteShader(_fragmentShaderHandle);
	glFuncs::ref().glDeleteProgram(_programHandle);
}

char* ShaderProgram::readShader(const char * p_shaderFile)
{
	FILE* filePointer = fopen(p_shaderFile, "rb");
	char* content = NULL;
	long numVal = 0;

	fseek(filePointer, 0L, SEEK_END);
	numVal = ftell(filePointer);
	fseek(filePointer, 0L, SEEK_SET);
	content = (char*)malloc((numVal + 1) * sizeof(char));
	fread(content, 1, numVal, filePointer);
	content[numVal] = '\0';
	fclose(filePointer);
	return content;
}

void ShaderProgram::setShaders(const char* p_vertex, const char* p_pixel, int &p_programHandle, int &p_vertexShaderHandle, int &p_fragmentShaderHandle)
{
	GLint status = 0;

	p_programHandle = glFuncs::ref().glCreateProgram();
	p_vertexShaderHandle = glFuncs::ref().glCreateShader(GL_VERTEX_SHADER);
	p_fragmentShaderHandle = glFuncs::ref().glCreateShader(GL_FRAGMENT_SHADER);

	setShader(p_vertex, p_programHandle, p_vertexShaderHandle);
	setShader(p_pixel, p_programHandle, p_fragmentShaderHandle);

	glFuncs::ref().glLinkProgram(p_programHandle);
	glFuncs::ref().glGetObjectParameterivARB(p_programHandle, GL_OBJECT_LINK_STATUS_ARB, &status);
	if (!status) {
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glFuncs::ref().glGetInfoLogARB(p_programHandle, maxInfoLogSize, NULL, infoLog);
		std::cout << infoLog;
	}
}

void ShaderProgram::setShader(const char* p_file, int &p_programHandle, int &p_shaderHandle)
{
	GLint status = 0;

	char* shader = readShader(p_file);

	glFuncs::ref().glShaderSource(p_shaderHandle, 1, (const char**)&shader, NULL);

	glFuncs::ref().glCompileShader(p_shaderHandle);

	glFuncs::ref().glGetObjectParameterivARB(p_shaderHandle, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if (!status)
	{
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glFuncs::ref().glGetInfoLogARB(p_shaderHandle, maxInfoLogSize, NULL, infoLog);
		std::cout << infoLog;
	}

	glFuncs::ref().glAttachShader(p_programHandle, p_shaderHandle);
}

void ShaderProgram::bindAttributes() {}

void ShaderProgram::bindAttribute(int attribute, const char* variableName)
{
	glFuncs::ref().glBindAttribLocation(_programHandle, attribute, variableName);
}

void ShaderProgram::getAllUniformLocations() {}

int ShaderProgram::getUniformLocation(const char * p_uniformName)
{
	return glFuncs::ref().glGetUniformLocation(_programHandle, p_uniformName);
}

void ShaderProgram::loadInt(int p_location, int p_value)
{
	glFuncs::ref().glUniform1i(p_location, p_value);
}

void ShaderProgram::loadFloat(int p_location, float p_value)
{
	glFuncs::ref().glUniform1f(p_location, p_value);
}

void ShaderProgram::loadVector(int p_location, glm::vec3 &p_value)
{
	glFuncs::ref().glUniform3f(p_location, p_value.x, p_value.y, p_value.z);
}

void ShaderProgram::loadVector(int p_location, glm::vec4 &p_value)
{
	glFuncs::ref().glUniform4f(p_location, p_value.x, p_value.y, p_value.z, p_value.w);
}

void ShaderProgram::loadBoolean(int p_location, bool p_value)
{
	glFuncs::ref().glUniform1f(p_location, p_value ? 1.0f : 0.0f);
}

void ShaderProgram::loadMatrix(int p_location, glm::mat4 &p_matrix)
{
	glFuncs::ref().glUniformMatrix4fv(p_location, 1, GL_FALSE, &p_matrix[0][0]);
}
