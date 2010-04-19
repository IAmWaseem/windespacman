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
	Tile(int pGridX, int pGridY, int pTileX, int pTileY, bool pTransparant, int pDepth);

	int TileWidth();
	int TileHeight();
	int GridX;
	int GridY;
	int TileX;
	int TileY;
	int Depth;
	float DepthFactor();
	bool Transparant;
	int PixelPositionX();
	int PixelPositionY();
	~Tile(void);
};
