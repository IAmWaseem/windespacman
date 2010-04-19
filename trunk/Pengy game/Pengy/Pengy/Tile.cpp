#include "Tile.h"

int Tile::tileW = 64;
int Tile::tileH = 64;

Tile::Tile(void)
{
	
}
Tile::Tile(int pGridX, int pGridY, int pTileX, int pTileY)
{
	GridX = pGridX;
	GridY = pGridY;
	TileX = pTileX;
	TileY = pTileY;
	Transparant = false;
	Depth = 0;
}
Tile::Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant)
{
	GridX = pGridX;
	GridY = pGridY;
	TileX = pTileX;
	TileY = pTileY;
	Transparant = pTransparant;
	Depth = 0;
}
Tile::Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant, int pDepth)
{
	GridX = pGridX;
	GridY = pGridY;
	TileX = pTileX;
	TileY = pTileY;
	Transparant = pTransparant;
	Depth = pDepth;
}
float Tile::DepthFactor()
{
	if(Depth == 0)
		return 1.00f;
	else if(Depth == 1)
		return 1.20f;
	else if(Depth == 2)
		return 1.50f;
	else if(Depth == 3)
		return 4.00f;
	else
		return 1.00f;
}
int Tile::PixelPositionX()
{
	return GridX * tileW;
}
int Tile::PixelPositionY()
{
	return GridY * tileH;
}
int Tile::TileHeight()
{
	return tileH;
}
int Tile::TileWidth()
{
	return tileW;
}
Tile::~Tile(void)
{
	
}
