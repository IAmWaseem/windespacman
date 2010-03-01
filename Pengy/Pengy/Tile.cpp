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
}
Tile::Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant)
{
	GridX = pGridX;
	GridY = pGridY;
	TileX = pTileX;
	TileY = pTileY;
	Transparant = pTransparant;
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
