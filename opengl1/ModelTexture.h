#include "Utility.h"

#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

class ModelTexture
{
public:
	explicit ModelTexture() : ModelTexture(-1) 
	{
		_shineDamper = 1.0f;
		_reflectivity = 0.0f;
	};
	explicit ModelTexture(int p_id) : _textureID(p_id) {};
	~ModelTexture();

	int getTextureID() const;
	float getShineDamper() const;
	float getReflectivity() const;
	void setShineDamper(float p_shineDamper);
	void setReflectivity(float p_reflectivity);

private:
	int _textureID;
	float _shineDamper;
	float _reflectivity;
};

#endif MODEL_TEXTURE_H