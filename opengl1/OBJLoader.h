#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include "glm/glm.hpp"
#include "RawModel.h"
#include "Loader.h"

#ifndef OBJLOADER_H
#define OBJLOADER_H

bool loadOBJ(
	const char * p_path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned int> & out_indices
);

RawModel loadOBJ(const char* p_path, Loader &p_loader);

#endif