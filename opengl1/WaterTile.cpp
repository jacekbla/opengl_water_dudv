#include "WaterTile.h"

const float WaterTile::TILE_SIZE = 5.0f;

WaterTile::~WaterTile()
{
}

float WaterTile::getHeight() const
{
	return _height;
}

float WaterTile::getX() const
{
	return _x;
}

float WaterTile::getZ() const
{
	return _z;
}
