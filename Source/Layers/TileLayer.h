#pragma once

#include "Layer.h"

#include <vector>

#include "../AssetLoading/Asset.h"

struct Tileset
{
	// INFO: The ID of the first & last tiles in the tileset
	int firstID;
	int lastID;

	// INFO: The number of rows & columns in the tileset
	int numRows;
	int numColumns;

	// INFO: The number of tiles in the tileset
	int numTiles;

	// INFO: The size of each individual tile in the tileset
	int tileSize;

	// INFO: The texture of the tileset used to draw the tiles (Also contains the filepath to the texture)
	Asset texture;

	Tileset() : firstID(0), lastID(0), numRows(0), numColumns(0), numTiles(0), tileSize(0) {}
};

class TileLayer : public Layer
{
public:
	TileLayer(int _tileSize, int _numRows, int _numColumns, const std::vector<std::vector<int>>& _tilemap, const std::vector<Tileset>& _tilesets);
	~TileLayer() = default;

	virtual void Draw() override;

	inline const std::vector<std::vector<int>>& GetTilemap() const { return tilemap; }
	inline const std::vector<Tileset>& GetTilesets() const { return tilesets; }

private:
	int tileSize; // INFO: The size of each individual tile in the tile map, to accurately draw the tiles
	int numRows; // INFO: The number of rows in the tile map
	int numColumns; // INFO: The number of columns in the tile map

	std::vector<std::vector<int>> tilemap; // INFO: The tilemap, a 2D vector of integer IDs representing the tiles in the map
	std::vector<Tileset> tilesets; // INFO: All the tilesets used to draw the tiles in the map
};

