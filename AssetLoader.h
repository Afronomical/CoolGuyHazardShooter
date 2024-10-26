#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Source/Vector2/Vector2.h"
class AssetLoader
{
public:
	class Asset
	{
	public:
		Asset();
		
		const int GetID();
	private:
		
		int id;
		
		const char* filepath;

		static int assetCount; 

		const char* GetFilepath();
	};

public:
#pragma region SDLFunctions
	static void SetRenderer(SDL_Renderer* renderer);

	static void Clean();
#pragma endregion SDLFunctions

#pragma region Loaders

	static Asset LoadTexture(const char* filepath);

	static Asset LoadFont(const char* filepath);

	static Asset LoadMusic(const char* filepath);

	static Asset LoadSFX(const char* filepath);
#pragma endregion Loaders
	static void DrawStatic(const Asset& texture, const Vector2& position, float width, float height, float scale, SDL_RendererFlip flip);

	static void DrawDynamic(const Asset& texture, const Vector2& position, float width, float height, float scrollSpeed, float scale, SDL_RendererFlip flip);

	static void DrawAnimation(const Asset& texture, const Vector2& position, float width, float height, int row, int frame, float scrollSpeed, float scale, SDL_RendererFlip flip);

	static void PlayMusic(const Asset& music, int loops);

	static void PlaySFX(const Asset& sfx, int loops);

	static void SetMusicVolume(const Asset& Music, int volume);

	static void SetSFXVolume(const Asset& SFX, int volume);

	static void SetFontSize(const Asset& font, int size);

	static TTF_Font* GetFont(const Asset& font);





};

