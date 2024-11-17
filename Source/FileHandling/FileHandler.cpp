#include "FileHandler.h"

#include "../Collision/Collider.h"
#include "../Debugging/Debug.h"
#include "../GameObject/GameObject.h"
#include "../Debugging/MemoryLeakDetector.h"

std::unordered_map<std::string, std::shared_ptr<Map>> FileHandler::mapLib{};

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

std::weak_ptr<Map> FileHandler::GetMap(const std::string& name)
{
	if (!IsMapLoaded(name))
	{
		Debug::LogWarning("Map with name: " + name + " is not loaded!");
		return std::weak_ptr<Map>{};
	}

	// INFO: Get the first layer of the map and dynamically cast it to a TileLayer
	TileLayer* collisionLayer = dynamic_cast<TileLayer*>(mapLib[name]->GetLayer(0));
	
	// INFO: Set the map collision data in the Collider handler to the collision layer's tilemap
	if (collisionLayer != nullptr)
		Collider::Handler::SetMapCollisionLayer(collisionLayer);

	//getlayer1 for GO layer 
	TileLayer* goLayer = dynamic_cast<TileLayer*>(mapLib[name]->GetLayer(1));

	if (goLayer != nullptr)
		GameObject::Handler::SetGameObjectsLayer(goLayer);


	return IsMapLoaded(name) ? mapLib[name] : nullptr;
}

bool FileHandler::ParseMap(const std::string& name, const std::string& filepath)
{
	// INFO: Load the XML document
	TiXmlDocument doc{};

	if (!doc.LoadFile(filepath))
	{
		Debug::LogError("Failed to load XML file: " + filepath);
		return false;
	}

	// INFO: Get the root element of the XML document
	TiXmlElement* rootElement = doc.RootElement();

	if (rootElement == nullptr)
	{
		Debug::LogError("Failed to get root element from XML file: " + filepath);
		return false;
	}

	int numRows = 0;
	int numColumns = 0;
	int tileSize = 0;

	// INFO: Get the map attributes from the root element
	rootElement->Attribute("height", &numRows);
	rootElement->Attribute("width", &numColumns);
	rootElement->Attribute("tilewidth", &tileSize);

	// INFO: Parse the tilesets from the root element
	std::vector<Tileset> tilesets;

	for (TiXmlElement* i = rootElement->FirstChildElement(); i != nullptr; i = i->NextSiblingElement())
	{
		if (i->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(i));
		}
	}

	// INFO: Parse the tile layers from the root element
	std::shared_ptr<Map> map = std::make_shared<Map>();

	for (TiXmlElement* i = rootElement->FirstChildElement(); i != nullptr; i = i->NextSiblingElement())
	{
		if (i->Value() == std::string("layer"))
		{
			map->AddLayer(ParseTileLayer(i, tilesets, tileSize, numRows, numColumns));
		}
	}

	// INFO: Add the map to the map library
	mapLib[name] = std::move(map);

	return true;
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

std::unique_ptr<TileLayer> FileHandler::ParseTileLayer(TiXmlElement* layerElement, const std::vector<Tileset>& tilesets, int tileSize, int numRows, int numColumns)
{
	// INFO: Get the data element from the layer element
	TiXmlElement* dataElement{};

	for (TiXmlElement* i = layerElement->FirstChildElement(); i != nullptr; i = i->NextSiblingElement())
	{
		if (i->Value() == std::string("data"))
		{
			dataElement = i;
			break;
		}
	}

	if (dataElement == nullptr)
	{
		Debug::LogError("Failed to find data element in layer element!");
		return nullptr;
	}

	// INFO: Get the data from the data element
	std::string data = dataElement->GetText();

	if (data.empty())
	{
		Debug::LogError("Failed to get data from data element!");
		return nullptr;
	}

	std::istringstream dataStream(data);
	std::string tileID;

	// INFO: Create the tilemap
	std::vector<std::vector<int>> tilemap(numRows, std::vector<int>(numColumns, 0));

	// INFO: Parse the data and fill the tilemap
	for (int row = 0; row < numRows; ++row)
	{
		for (int column = 0; column < numColumns; ++column)
		{
			std::getline(dataStream, tileID, ',');

			// INFO: Convert the tile ID to an integer and store it in the tilemap
			tilemap[row][column] = std::stoi(tileID);

			// INFO: Break if the data stream is no longer good (No more data to read)
			if (!dataStream.good())
				break;
		}
	}

	return std::make_unique<TileLayer>(tileSize, numRows, numColumns, tilemap, tilesets);
}
