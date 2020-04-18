#include "Utility.h"
#include "RawModel.h"
#include "ModelTexture.h"

#ifndef TEXTURE_MODEL_H
#define TEXTURE_MODEL_H

class TexturedModel
{
public:
	explicit TexturedModel() : TexturedModel(RawModel(), ModelTexture()) {};
	explicit TexturedModel(RawModel p_model, ModelTexture p_texture) : _rawModel(p_model), _texture(p_texture) {};
	~TexturedModel();

	RawModel getRawModel() const;
	ModelTexture getTexture() const;
	bool operator<(const TexturedModel& p_other) const;

private:
	RawModel _rawModel;
	ModelTexture _texture;
};


#endif TEXTURE_MODEL_H