#pragma once

#include "Layer.h"
#include <vector>
#include "../AssetLoading/Asset.h"
#include "../GameObject/GameObject.h"
#include "../Enemies/BaseEnemy.h"
#include "../Enemies/WalkingEnemy.h"
#include "../Enemies/JumpingEnemy.h"



class EnemyLayer : public Layer
{
public:
	EnemyLayer();
	~EnemyLayer() override {};

	void Init(int _tileSize, int _numRows, int _numColumns, const std::vector<std::vector<int>>& _tilemap, const std::vector<Tileset>& _tilesets, const Vector2& _position);

	inline const std::vector<GameObject>& GetEnemy() const { return enemies; }

private:
	std::vector<GameObject> enemies; // INFO: All enemies in the map
};

