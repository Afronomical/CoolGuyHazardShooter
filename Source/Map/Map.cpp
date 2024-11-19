#include "Map.h"

#include "../Debugging/Debug.h"
#include "../Debugging/MemoryLeakDetector.h"

void Map::Draw()
{
	// INFO: Go through all map layers and draw them
	for (const auto& layer : mapLayers)
	{
		layer->Draw();
	}
}

Layer* Map::GetLayer(int index)
{
	// INFO: Check to see if the index is out of bounds
	if (index < 0 || index >= mapLayers.size())
	{
		Debug::LogError("Map::GetLayer: Index out of bounds!");
		return nullptr;
	}

	return mapLayers[index].get();
}
