#include "TileLayer.h"

TileLayer::TileLayer(int _tileSize, int _numRows, int _numColumns, const std::vector<std::vector<int>>& _tilemap, const std::vector<Tileset>& _tilesets) 
					 : tileSize(_tileSize), numRows(_numRows), numColumns(_numColumns), tilemap(_tilemap), tilesets(_tilesets)
{
}

void TileLayer::Draw()
{
}
