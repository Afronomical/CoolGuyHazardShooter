#include "TileLayer.h"

#include "../AssetLoading/AssetHandler.h"
#include "../Debugging/MemoryLeakDetector.h"

TileLayer::TileLayer(int _tileSize, int _numRows, int _numColumns, const std::vector<std::vector<int>>& _tilemap, const std::vector<Tileset>& _tilesets) 
					 : tileSize(_tileSize), numRows(_numRows), numColumns(_numColumns), tilemap(_tilemap), tilesets(_tilesets)
{
	// INFO: Load all the textures of the tilesets used by the tile layer into the AssetHandler
	for (size_t i = 0; i < tilesets.size(); i++)
	{
		// INFO: Create the filepath for the texture using the textures path and the remaining path
		std::string textureFilepath = "Assets/Maps/" + tilesets[i].texture.GetFilepath();

		tilesets[i].texture = AssetHandler::LoadTexture(textureFilepath);
	}
}

void TileLayer::Draw(const Vector2& position)
{
	for (size_t mapRow = 0; mapRow < numRows; mapRow++)
	{
		for (size_t mapColumn = 0; mapColumn < numColumns; mapColumn++)
		{
			int tileID = tilemap[mapRow][mapColumn];

			// INFO: Skip empty tiles
			if (tileID == 0)
				continue;

			// INFO: Find the tileset that contains the tile with the given ID
			//       granted theres more than one tileset
			int tilesetIndex = 0;

			if (tilesets.size() > 1)
			{
				for (size_t i = 0; i < tilesets.size(); i++)
				{
					// INFO: Check if the tile ID is within the range of the current tileset
					if (tileID >= tilesets[i].firstID && tileID <= tilesets[i].lastID)
					{
						// INFO: Convert the tileID to the index of the tile in the tileset
						tileID -= tilesets[i].firstID;
						tilesetIndex = (int)i;
					}
				}
			}

			// INFO: Calculate the row and column of the tile in the tileset
			Tileset selectedTileset = tilesets[tilesetIndex];
			int tileRow = tileID / selectedTileset.numColumns;
			int tileColumn = tileID - tileRow * selectedTileset.numColumns - 1;

			// INFO: Edge case for tiles in the last column
			if (tileID % selectedTileset.numColumns == 0)
			{
				tileRow--;
				tileColumn = selectedTileset.numColumns - 1;
			}

			// INFO: Draw the tile
			//add position so that it wont be drawn at 0,0
			Vector2 tilePos = position + Vector2((float)(mapColumn * selectedTileset.tileSize), (float)(mapRow * selectedTileset.tileSize));

			AssetHandler::DrawTile(selectedTileset.texture, tilePos, selectedTileset.tileSize, tileRow, tileColumn);
		}
	}
}
