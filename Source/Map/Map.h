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

	void SetDimensions(int rows, int cols, int tileSize) {
		this->numRows = rows;
		this->numColumns = cols;
		this->tileSize = tileSize;
	}

	int GetRows() const { return numRows; }
	int GetColumns() const { return numColumns; }
	int GetTileSize() const { return tileSize; }

private:
	std::vector<std::unique_ptr<Layer>> mapLayers;

	int numRows;
	int numColumns;
	int tileSize;
};

