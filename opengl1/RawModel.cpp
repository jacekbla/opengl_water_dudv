#include "RawModel.h"

RawModel::~RawModel()
{
}

int RawModel::getVaoID() const
{
	return _vaoId;
}

int RawModel::getVertexCount() const
{
	return _vertexCount;
}
