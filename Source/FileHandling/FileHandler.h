#pragma once

#include <string>
#include <unordered_map>

#include "../Externals/TinyXML/tinyxml.h"

#include "../Map/Map.h"
#include "../Layers/TileLayer.h"

class FileHandler
{
public:
	bool LoadMap(const std::string& name, const std::string& filepath);

private:
	bool ParseMap(const std::string& name, const std::string& filepath);
	Tileset ParseTileset(TiXmlElement* tilesetElement);
	TileLayer* ParseTileLayer(TiXmlElement* layerElement, const std::vector<Tileset>& tilesets, int tileSize, int numRows, int numColumns);

	inline bool IsMapLoaded(const std::string& name) const { return mapLib.find(name) != mapLib.end(); }

private:
	std::unordered_map<std::string, std::unique_ptr<Map>> mapLib;

private:
	FileHandler() = delete;
	~FileHandler() = delete;
	FileHandler(const FileHandler&) = delete;
	FileHandler& operator=(const FileHandler&) = delete;
};

