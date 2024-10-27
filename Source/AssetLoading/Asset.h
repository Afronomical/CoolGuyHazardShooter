#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <unordered_map>

#include "../Vector2/Vector2.h"

class Asset
{
	friend class AssetHandler;

public:
	Asset();

	inline const int GetID() const { return id; }
	inline const char* GetFilepath() const { return filepath; }

	inline bool operator==(const Asset& other) const { return id == other.id && filepath == other.filepath; }

private:
	Asset(int _id, const char* _filepath);

	void SetFilepath(const char* _filepath) { filepath = _filepath; }

private:
	int id;
	const char* filepath;

	static unsigned int assetCount;
	static Asset invalidAsset;
};

namespace std
{
	template<>
	struct std::hash<Asset>
	{
		std::size_t operator()(const Asset& asset) const
		{
			return ((std::hash<int>()(asset.GetID()) 
				   ^ (std::hash<const char*>()(asset.GetFilepath()) << 1)) >> 1);
		}
	};
}
