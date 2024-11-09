#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>
#include <unordered_map>

#include "../Vector2/Vector2.h"

class Asset
{
	friend class AssetHandler;
	friend class FileHandler;

public:
	Asset();

	/// @brief The unique ID of the asset that is used to identify the asset
	inline const int GetID() const { return id; }

	/// @brief The filepath of the asset used to check if the asset is already loaded
	inline const std::string& GetFilepath() const { return filepath; }

	inline bool operator==(const Asset& other) const { return id == other.id && filepath == other.filepath; }

private:
	Asset(int _id, const std::string& _filepath);

	void SetFilepath(const std::string& _filepath) { filepath = _filepath; }

private:
	int id;
	std::string filepath;

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
				   ^ (std::hash<std::string>()(asset.GetFilepath()) << 1)) >> 1);
		}
	};
}
