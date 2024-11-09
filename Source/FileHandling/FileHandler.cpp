#include "FileHandler.h"

#include "../Debugging/Debug.h"

bool FileHandler::LoadMap(const std::string& name, const std::string& filepath)
{
	// INFO: Check if the map is already loaded
	if (IsMapLoaded(name))
	{
		Debug::LogWarning("Map with name: " + name + " is already loaded!");
		return false;
	}

	// INFO: Parse the map
	if (!ParseMap(name, filepath))
	{
		Debug::LogError("Failed to parse map with name: " + name + " from file: " + filepath);
		return false;
	}

	return true;
}

bool FileHandler::ParseMap(const std::string& name, const std::string& filepath)
{
	return false;
}

Tileset FileHandler::ParseTileset(TiXmlElement* tilesetElement)
{
	Tileset tileset;

	// INFO: Copy attributes from the XML element to the tileset
	tilesetElement->Attribute("firstgid", &tileset.firstID);
	tilesetElement->Attribute("tilecount", &tileset.numTiles);
	tileset.lastID = tileset.firstID + tileset.numTiles - 1;

	tilesetElement->Attribute("columns", &tileset.numColumns);
	tileset.numRows = tileset.numTiles / tileset.numColumns;

	tilesetElement->Attribute("tilewidth", &tileset.tileSize);

	TiXmlElement* imageElement = tilesetElement->FirstChildElement("image");
	tileset.texture.SetFilepath(imageElement->Attribute("source"));

	return tileset;
}

TileLayer* FileHandler::ParseTileLayer(TiXmlElement* layerElement, const std::vector<Tileset>& tilesets, int tileSize, int numRows, int numColumns)
{
	return nullptr;
}
