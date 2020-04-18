#include "TexturedModel.h"


TexturedModel::~TexturedModel()
{
}

RawModel TexturedModel::getRawModel() const
{
	return _rawModel;
}

ModelTexture TexturedModel::getTexture() const
{
	return _texture;
}

bool TexturedModel::operator<(const TexturedModel& p_other) const
{
	return this < &p_other;
}