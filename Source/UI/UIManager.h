#pragma once

#include "../AssetLoading/AssetHandler.h"
#include "../Input/InputHandler.h"
#include "../Camera/Camera.h"
#include "../Time/Time.h"
#include <memory>
#include <vector>
#include <functional>
#include <string>


class UIManager
{
public:
    UIManager(std::shared_ptr<Camera> camera, std::shared_ptr<AssetHandler> assetHandler);
    ~UIManager();

    void Init();
    void Update(); // Removed deltaTime parameter
    void Render(SDL_Renderer* renderer);
    void HandleInput(InputHandler& inputHandler);

    void AddMenuOption(const std::string& text, std::function<void()> action);

    
    // Helper function for rendering text
    void RenderText(const std::string& text, const SDL_Rect& rect, SDL_Renderer* renderer);

private:
    struct MenuOption
    {
        std::string text;
        std::function<void()> action;
        SDL_Rect bounds; // Rectangle area for the option button
    };

    std::shared_ptr<Camera> camera;
    std::shared_ptr<AssetHandler> assetHandler;

    std::vector<MenuOption> menuOptions;
    int selectedOption = 0;


    // Helper function to handle selection highlighting
    void UpdateMenuSelection();

};
