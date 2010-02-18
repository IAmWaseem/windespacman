#pragma once

class Tile
{
private:

public:
	Tile(void);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant);
	static const int TileWidth = 48;
	static const int TileHeight = 48;
	int GridX;
	int GridY;
	int TileX;
	int TileY;
	bool Transparant;
	int PixelPositionX();
	int PixelPositionY();
	~Tile(void);
};
