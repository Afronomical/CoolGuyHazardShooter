#pragma once

#include <memory>
#include <vector>

class Layer;

class Map
{
public:
	Map() = default;

	void Draw();

	inline const std::vector<std::unique_ptr<Layer>>& GetMapLayers() const { return mapLayers; }

private:
	std::vector<std::unique_ptr<Layer>> mapLayers;
};

