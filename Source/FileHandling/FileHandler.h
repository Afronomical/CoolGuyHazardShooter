#pragma once

#include <string>
#include <unordered_map>

#include "../Externals/TinyXML/tinyxml.h"

#include "../Map/Map.h"
#include "../Layers/TileLayer.h"

class FileHandler
{
public:
	static bool LoadMap(const std::string& name, const std::string& filepath);

	static inline Map* GetMap(const std::string& name) { return IsMapLoaded(name) ? mapLib[name].get() : nullptr; }

private:
	static bool ParseMap(const std::string& name, const std::string& filepath);
	static Tileset ParseTileset(TiXmlElement* tilesetElement);
	static std::unique_ptr<TileLayer> ParseTileLayer(TiXmlElement* layerElement, const std::vector<Tileset>& tilesets, int tileSize, int numRows, int numColumns);

	static inline bool IsMapLoaded(const std::string& name) { return mapLib.find(name) != mapLib.end(); }

private:
	static std::unordered_map<std::string, std::unique_ptr<Map>> mapLib;

private:
	FileHandler() = delete;
	~FileHandler() = delete;
	FileHandler(const FileHandler&) = delete;
	FileHandler& operator=(const FileHandler&) = delete;
};

