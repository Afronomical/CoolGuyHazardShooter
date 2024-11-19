#pragma once

#include <memory>
#include <vector>

#include "../Layers/Layer.h"

class Map
{
public:
	Map() = default;
	~Map() = default;

	void Draw();

	Layer* GetLayer(int index);
	inline const std::vector<std::unique_ptr<Layer>>& GetMapLayers() const { return mapLayers; }

	inline void AddLayer(std::unique_ptr<Layer> layer) { mapLayers.push_back(std::move(layer)); }

private:
	std::vector<std::unique_ptr<Layer>> mapLayers;
};

