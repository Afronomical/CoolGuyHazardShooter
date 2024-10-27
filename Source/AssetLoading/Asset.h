#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <unordered_map>

#include "../Vector2/Vector2.h"

class Asset
{
public:
	class Handler
	{
	public:
		static Asset LoadTexture(const char* filepath);
		static Asset LoadFont(const char* filepath, int ptSize);
		static Asset LoadMusic(const char* filepath);
		static Asset LoadSFX(const char* filepath);

		static void Clean();

		static void DrawStatic(const Asset& texture, const Vector2& position, float width, float height, float scale, SDL_RendererFlip flip);
		static void DrawDynamic(const Asset& texture, const Vector2& position, float width, float height, float scrollSpeed, float scale, SDL_RendererFlip flip);
		static void DrawAnimation(const Asset& texture, const Vector2& position, float width, float height, int row, int frame, float scrollSpeed, float scale, SDL_RendererFlip flip);

		static inline bool IsTextureValid(const Asset& texture) { return textureLib.find(texture) != textureLib.end(); }
		static bool IsAudioValid(const Asset& audio, bool isMusic = false);
		static inline bool IsFontValid(const Asset& font) { return fontLib.find(font) != fontLib.end(); }

		static void PlayMusic(const Asset& music, int loops = 0);
		static void PlaySFX(const Asset& sfx, int loops = 0);

		static inline void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }
		static void SetSFXVolume(const Asset& sfx, int volume);

		static void SetFontSize(const Asset& font, int size);
		static TTF_Font* GetFont(const Asset& font);

		static inline void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }

	private:
		static std::unordered_map<Asset, SDL_Texture*> textureLib;
		static std::unordered_map<Asset, Mix_Music*> musicLib;
		static std::unordered_map<Asset, Mix_Chunk*> sfxLib;
		static std::unordered_map<Asset, TTF_Font*> fontLib;

		static SDL_Renderer* renderer;
	};

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

