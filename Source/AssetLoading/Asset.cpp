#include "Asset.h"

#include "../Debugging/Debug.h"

#pragma region StaticAssetMembers
unsigned int Asset::assetCount = 0;
Asset Asset::invalidAsset = Asset(-1, nullptr);
#pragma endregion StaticAssetMembers

#pragma region StaticHandlerMembers
std::unordered_map<Asset, SDL_Texture*> Asset::Handler::textureLib;
std::unordered_map<Asset, Mix_Music*> Asset::Handler::musicLib;
std::unordered_map<Asset, Mix_Chunk*> Asset::Handler::sfxLib;
std::unordered_map<Asset, TTF_Font*> Asset::Handler::fontLib;

SDL_Renderer* Asset::Handler::renderer = nullptr;
#pragma endregion StaticHandlerMembers

#pragma region HandlerMethods
Asset Asset::Handler::LoadTexture(const char* filepath)
{
	// INFO: Check if the texture is already loaded, if so return it
	for (auto& texture : textureLib)
	{
		if (strcmp(texture.first.GetFilepath(), filepath) == 0)
		{
			return texture.first;
		}
	}

	// INFO: Load the texture
	SDL_Surface* sdlSurface = IMG_Load(filepath);

	if (sdlSurface == nullptr)
	{
		Debug::LogError("Asset::Handler::LoadTexture: Failed to initialise Surface. SDL error: " + std::string(SDL_GetError()));
		return invalidAsset;
	}

	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);

	if (sdlTexture == nullptr)
	{
		Debug::LogError("TextureHandler::LoadTexture: Failed to initialise Texture. SDL error: " + std::string(SDL_GetError()));
		return invalidAsset;
	}

	SDL_FreeSurface(sdlSurface);

	// INFO: Create the asset and add it to the library
	Asset asset;
	asset.SetFilepath(filepath);

	textureLib[asset] = sdlTexture;

	return asset;
}
Asset Asset::Handler::LoadFont(const char* filepath, int ptSize)
{
	// INFO: Check if the font is already loaded, if so return it
	for (auto& font : fontLib)
	{
		if (strcmp(font.first.GetFilepath(), filepath) == 0)
		{
			return font.first;
		}
	}

	// INFO: Load the font
	TTF_Font* sdlFont = TTF_OpenFont(filepath, ptSize);

	if (sdlFont == nullptr)
	{
		Debug::LogError("Asset::Handler::LoadFont: Failed to initialise Font. TTF error: " + std::string(TTF_GetError()));
		return invalidAsset;
	}

	// INFO: Create the asset and add it to the library
	Asset asset;
	asset.SetFilepath(filepath);

	fontLib[asset] = sdlFont;

	return asset;
}
Asset Asset::Handler::LoadMusic(const char* filepath)
{
	// INFO: Check if the music is already loaded, if so return it
	for (auto& music : musicLib)
	{
		if (strcmp(music.first.GetFilepath(), filepath) == 0)
		{
			return music.first;
		}
	}

	// INFO: Load the music
	Mix_Music* sdlMusic = Mix_LoadMUS(filepath);

	if (sdlMusic == nullptr)
	{
		Debug::LogError("Asset::Handler::LoadMusic: Failed to initialise Music. Mix error: " + std::string(Mix_GetError()));
		return invalidAsset;
	}

	// INFO: Create the asset and add it to the library
	Asset asset;
	asset.SetFilepath(filepath);

	musicLib[asset] = sdlMusic;

	return asset;
}
Asset Asset::Handler::LoadSFX(const char* filepath)
{
	// INFO: Check if the SFX is already loaded, if so return it
	for (auto& sfx : sfxLib)
	{
		if (strcmp(sfx.first.GetFilepath(), filepath) == 0)
		{
			return sfx.first;
		}
	}

	// INFO: Load the SFX
	Mix_Chunk* sdlSFX = Mix_LoadWAV(filepath);

	if (sdlSFX == nullptr)
	{
		Debug::LogError("Asset::Handler::LoadSFX: Failed to initialise SFX. Mix error: " + std::string(Mix_GetError()));
		return invalidAsset;
	}

	// INFO: Create the asset and add it to the library
	Asset asset;
	asset.SetFilepath(filepath);

	sfxLib[asset] = sdlSFX;

	return asset;
}

void Asset::Handler::Clean()
{
	// INFO: Clean the texture library
	for (auto& texture : textureLib)
	{
		SDL_DestroyTexture(texture.second);
	}

	textureLib.clear();

	// INFO: Clean the music library
	for (auto& music : musicLib)
	{
		Mix_FreeMusic(music.second);
	}

	musicLib.clear();

	// INFO: Clean the SFX library
	for (auto& sfx : sfxLib)
	{
		Mix_FreeChunk(sfx.second);
	}

	sfxLib.clear();

	// INFO: Clean the font library
	for (auto& font : fontLib)
	{
		TTF_CloseFont(font.second);
	}

	fontLib.clear();
}

void Asset::Handler::DrawStatic(const Asset& texture, const Vector2& position, float width, float height, float scale, SDL_RendererFlip flip)
{
	// INFO: Check if the texture is valid
	if (!IsTextureValid(texture))
	{
		Debug::LogWarning("Asset::Handler::DrawStatic: Invalid texture.");
		return;
	}

	// INFO: Create the destination rectangle
	SDL_Rect destRect = { static_cast<int>(position.X), static_cast<int>(position.Y), static_cast<int>(width * scale), static_cast<int>(height * scale) };

	// INFO: Draw the texture
	SDL_RenderCopyEx(renderer, textureLib[texture], nullptr, &destRect, 0.0, nullptr, flip);
}

void Asset::Handler::DrawDynamic(const Asset& texture, const Vector2& position, float width, float height, float scrollSpeed, float scale, SDL_RendererFlip flip)
{
	// INFO: Check if the texture is valid
	if (!IsTextureValid(texture))
	{
		Debug::LogWarning("Asset::Handler::DrawDynamic: Invalid texture.");
		return;
	}

	// INFO: Get camera position
	// Vector2 cameraPosition = ...;

	// INFO: Create the destination rectangle with the camera offset
	//SDL_Rect destRect = { static_cast<int>(position.X - cameraPosition.X), static_cast<int>(position.Y - cameraPosition.Y), static_cast<int>(width * scale), static_cast<int>(height * scale) };

	// INFO: Draw the texture
	//SDL_RenderCopyEx(renderer, textureLib[texture], nullptr, &destRect, 0.0, nullptr, flip);
}

void Asset::Handler::DrawAnimation(const Asset& texture, const Vector2& position, float width, float height, int row, int frame, float scrollSpeed, float scale, SDL_RendererFlip flip)
{
	// INFO: Check if the texture is valid
	if (!IsTextureValid(texture))
	{
		Debug::LogWarning("Asset::Handler::DrawAnimation: Invalid texture.");
		return;
	}

	// INFO: Get camera position
	// Vector2 cameraPosition = ...;

	// INFO: Create the source rectangle
	SDL_Rect srcRect = { frame * width, row * height, width, height };

	// INFO: Create the destination rectangle with the camera offset
	//SDL_Rect destRect = { static_cast<int>(position.X - cameraPosition.X), static_cast<int>(position.Y - cameraPosition.Y), static_cast<int>(width * scale), static_cast<int>(height * scale) };

	// INFO: Draw the texture
	//SDL_RenderCopyEx(renderer, textureLib[texture], &srcRect, &destRect, 0.0, nullptr, flip);
}

bool Asset::Handler::IsAudioValid(const Asset& audio, bool isMusic)
{
	if (isMusic)
	{
		return musicLib.find(audio) != musicLib.end();
	}
	else
	{
		return sfxLib.find(audio) != sfxLib.end();
	}
}

void Asset::Handler::PlayMusic(const Asset& music, int loops)
{
	// INFO: Check if the music is valid
	if (!IsAudioValid(music, true))
	{
		Debug::LogWarning("Asset::Handler::PlayMusic: Invalid music.");
		return;
	}

	// INFO: Play and validate the music
	if (Mix_PlayMusic(musicLib[music], loops) == -1)
	{
		Debug::LogError("Asset::Handler::PlayMusic: Failed to play music. Mix error: " + std::string(Mix_GetError()));
	}
}

void Asset::Handler::PlaySFX(const Asset& sfx, int loops)
{
	// INFO: Check if the SFX is valid
	if (!IsAudioValid(sfx))
	{
		Debug::LogWarning("Asset::Handler::PlaySFX: Invalid SFX.");
		return;
	}

	// INFO: Play and validate the SFX
	if (Mix_PlayChannel(-1, sfxLib[sfx], loops) == -1)
	{
		Debug::LogError("Asset::Handler::PlaySFX: Failed to play SFX. Mix error: " + std::string(Mix_GetError()));
	}
}

void Asset::Handler::SetSFXVolume(const Asset& sfx, int volume)
{
	// INFO: Check if the SFX is valid
	if (!IsAudioValid(sfx))
	{
		Debug::LogWarning("Asset::Handler::SetSFXVolume: Invalid SFX.");
		return;
	}

	// INFO: Set the SFX volume
	Mix_VolumeChunk(sfxLib[sfx], volume);
}
void Asset::Handler::SetFontSize(const Asset& font, int size)
{
	// INFO: Check if the font is valid
	if (!IsFontValid(font))
	{
		Debug::LogWarning("Asset::Handler::SetFontSize: Invalid font.");
		return;
	}

	// INFO: Set the font size
	TTF_SetFontSize(fontLib[font], size);
}
TTF_Font* Asset::Handler::GetFont(const Asset& font)
{
	// INFO: Check if the font is valid
	if (!IsFontValid(font))
	{
		Debug::LogWarning("Asset::Handler::GetFont: Invalid font.");
		return nullptr;
	}

	return fontLib[font];
}
#pragma endregion HandlerMethods

#pragma region AssetMethods
Asset::Asset() : id(assetCount++), filepath(nullptr)
{
}

Asset::Asset(int _id, const char* _filepath) : id(_id), filepath(_filepath)
{
}
#pragma endregion AssetMethods
