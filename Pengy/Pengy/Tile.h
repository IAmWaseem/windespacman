#pragma once

class Tile
{
private:
	static int tileW;
	static int tileH;
public:
	Tile(void);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY);
	Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant);
	int TileWidth();
	int TileHeight();
	int GridX;
	int GridY;
	int TileX;
	int TileY;
	bool Transparant;
	int PixelPositionX();
	int PixelPositionY();
	~Tile(void);
};
