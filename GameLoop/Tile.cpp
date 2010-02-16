#include "Tile.h"

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
	return GridX * Tile.TileWidth;
}
int Tile::PixelPositionY()
{
	return GridY * Tile.TileHeight;
}
Tile::~Tile(void)
{
	
}
