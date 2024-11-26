#pragma once

struct MapCollisionResult
{
	bool isCollidingLeftTile;
	bool isCollidingRightTile;

	MapCollisionResult() : isCollidingLeftTile(false), isCollidingRightTile(false) {}
};

