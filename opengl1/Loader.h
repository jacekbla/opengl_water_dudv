#include "RawModel.h"
#include "Utility.h"

#ifndef LOADER_H
#define LOADER_H

class Loader
{
public:
	explicit Loader();
	~Loader();

	RawModel loadToVAO(std::vector<float> p_positions, std::vector<float> p_colors, std::vector<float> p_texCoords, std::vector<float> p_normals, std::vector<unsigned int> p_indices);
	RawModel loadToVAO(std::vector<float> p_positions, int p_dimensions);
	void cleanUp();
	GLuint loadTexture(std::string p_fileName);

private:
	int createVAO();
	void storeDataInAtrributeList(int p_attributeNumber, int p_coordinateSize, std::vector<float> p_data);
	void unbindVAO();
	void bindIndicesBuffer(std::vector<unsigned int> p_indices);


	std::vector<GLuint> _vaos;
	std::vector<GLuint> _vbos;
	std::vector<GLuint> _textures;
};

#endif LOADER_H