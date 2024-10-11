#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!\n";
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    IMG_Init(IMG_INIT_PNG);

    return 0;
}

