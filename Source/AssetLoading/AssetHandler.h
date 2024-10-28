#pragma once

#include "Asset.h"

class AssetHandler
{
public:
	static Asset LoadTexture(const char* filepath);
	static Asset LoadFont(const char* filepath, int ptSize);
	static Asset LoadMusic(const char* filepath);
	static Asset LoadSFX(const char* filepath);

	static void Clean();

	/// @brief Used to draw static textures that do not change based on camera e.g. (UI)
	static void DrawStatic(const Asset& texture, const Vector2& position, float width, float height, float scale, SDL_RendererFlip flip);

	/// @brief Used to draw dynamic textures that change based on camera e.g. (Background, tilemap blocks)
	static void DrawDynamic(const Asset& texture, const Vector2& position, float width, float height, float scrollSpeed, float scale, SDL_RendererFlip flip);
	
	/// @brief Used to draw animated textures that change based on camera e.g. (Player, enemies)
	static void DrawAnimation(const Asset& texture, const Vector2& position, float width, float height, int row, int frame, float scrollSpeed, float scale, SDL_RendererFlip flip);

	/// @param loops : 0 = play once, -1 = loop indefinitely
	static void PlayMusic(const Asset& music, int loops = 0);

	/// @param loops : 0 = play once, -1 = loop indefinitely
	static void PlaySFX(const Asset& sfx, int loops = 0);

	/// @brief Sets the volume of the channel that the music is played on
	static inline void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }
	static void SetSFXVolume(const Asset& sfx, int volume);

	static void SetFontSize(const Asset& font, int size);
	static TTF_Font* GetFont(const Asset& font);

	static inline void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }

private:
	static inline bool IsTextureValid(const Asset& texture) { return textureLib.find(texture) != textureLib.end(); }
	static bool IsAudioValid(const Asset& audio, bool isMusic = false);
	static inline bool IsFontValid(const Asset& font) { return fontLib.find(font) != fontLib.end(); }

private:
	static std::unordered_map<Asset, SDL_Texture*> textureLib;
	static std::unordered_map<Asset, Mix_Music*> musicLib;
	static std::unordered_map<Asset, Mix_Chunk*> sfxLib;
	static std::unordered_map<Asset, TTF_Font*> fontLib;

	static SDL_Renderer* renderer;

private:
	AssetHandler() = delete;
	~AssetHandler() = delete;
	AssetHandler(const AssetHandler&) = delete;
	AssetHandler& operator=(const AssetHandler&) = delete;
};

