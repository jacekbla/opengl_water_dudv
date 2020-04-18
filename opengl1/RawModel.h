#ifndef RAW_MODEL_H
#define RAW_MODEL_H

class RawModel
{
public:
	explicit RawModel(int p_vaoId, int p_vertexCount)
		: _vaoId(p_vaoId),
		_vertexCount(p_vertexCount) {};
	explicit RawModel() : RawModel(0, 0) {};
	~RawModel();
	int getVaoID() const;
	int getVertexCount() const;

private:
	int _vaoId;
	int _vertexCount;
};

#endif RAW_MODEL_H
