#include "Loader.h"

struct BitMapFile
{
	int sizeX;
	int sizeY;
	unsigned char *data;
};

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile* getBMPData(std::string filename)
{
	BitMapFile *bmp = new BitMapFile;
	unsigned int size, offset, headerSize;

	// Read input file name.
	std::ifstream infile(filename.c_str(), std::ios::binary);

	// Get the starting point of the image data.
	infile.seekg(10);
	infile.read((char *)&offset, 4);

	// Get the header size of the bitmap.
	infile.read((char *)&headerSize, 4);

	// Get width and height values in the bitmap header.
	infile.seekg(18);
	infile.read((char *)&bmp->sizeX, 4);
	infile.read((char *)&bmp->sizeY, 4);

	// Allocate buffer for the image.
	size = bmp->sizeX * bmp->sizeY * 24;
	bmp->data = new unsigned char[size];

	// Read bitmap data.
	infile.seekg(offset);
	infile.read((char *)bmp->data, size);

	// Reverse color from bgr to rgb.
	int temp;
	for (int i = 0; i < size; i += 3)
	{
		temp = bmp->data[i];
		bmp->data[i] = bmp->data[i + 2];
		bmp->data[i + 2] = temp;
	}

	return bmp;
}




Loader::Loader()
{}

Loader::~Loader()
{}

RawModel Loader::loadToVAO(std::vector<float> p_positions, std::vector<float> p_colors, std::vector<float> p_texCoords, std::vector<float> p_normals, std::vector<unsigned int> p_indices)
{
	int vaoID = createVAO();
	bindIndicesBuffer(p_indices);
	storeDataInAtrributeList(0, 3, p_positions);
	storeDataInAtrributeList(1, 3, p_colors);
	storeDataInAtrributeList(2, 2, p_texCoords);
	storeDataInAtrributeList(3, 3, p_normals);
	unbindVAO();

	return RawModel(vaoID, p_indices.size());
}

RawModel Loader::loadToVAO(std::vector<float> p_positions, int p_dimensions) 
{
	int vaoID = createVAO();
	storeDataInAtrributeList(0, p_dimensions, p_positions);
	unbindVAO();
	return RawModel(vaoID, p_positions.size() / p_dimensions);
}

void Loader::cleanUp()
{
	glFuncs::ref().glDeleteVertexArrays(_vaos.size(), _vaos.data());
	glFuncs::ref().glDeleteVertexArrays(_vbos.size(), _vbos.data());
	glDeleteTextures(_textures.size(), _textures.data());
}

GLuint Loader::loadTexture(std::string p_fileName)
{
	BitMapFile* image;
	image = getBMPData(p_fileName);
	GLuint texID;
	glGenTextures(1, &texID);
	_textures.push_back(texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);

	return texID;
}

int Loader::createVAO()
{
	GLuint vaoID = 1;
	glFuncs::ref().glGenVertexArrays(1, &vaoID);
	_vaos.push_back(vaoID);
	glFuncs::ref().glBindVertexArray(vaoID);
	
	return vaoID;
}

void Loader::storeDataInAtrributeList(int p_attributeNumber, int p_coordinateSize, std::vector<float> p_data)
{
	GLuint vbo;
	glFuncs::ref().glGenBuffers(1, &vbo);
	_vbos.push_back(vbo);
	glFuncs::ref().glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glFuncs::ref().glBufferData(GL_ARRAY_BUFFER, p_data.size() * sizeof(float), p_data.data(), GL_STATIC_DRAW);
	glFuncs::ref().glVertexAttribPointer(p_attributeNumber, p_coordinateSize, GL_FLOAT, GL_FALSE, 0, NULL);
	glFuncs::ref().glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
	glFuncs::ref().glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> p_indices)
{
	GLuint vboID;
	glFuncs::ref().glGenBuffers(1, &vboID);
	_vbos.push_back(vboID);
	glFuncs::ref().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glFuncs::ref().glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(unsigned int), p_indices.data(), GL_STATIC_DRAW);
	//glFuncs::ref().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}