#include "Map.h"

void Map::Draw()
{
	// INFO: Go through all map layers and draw them
	for (const auto& layer : mapLayers)
	{
		layer->Draw();
	}
}
