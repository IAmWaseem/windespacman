#pragma once

class Tile
{
private:
	static const int TileWidth = 64;
	static const int TileHeight = 64;
	

public:
	Tile(void);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant);
	int GridX;
	int GridY;
	int TileX;
	int TileY;
	bool Transparant;
	int PixelPositionX();
	int PixelPositionY();
	~Tile(void);
};
