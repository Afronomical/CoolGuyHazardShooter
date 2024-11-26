#include "UIManager.h"

UIManager::UIManager(std::shared_ptr<Camera> camera, std::shared_ptr<AssetHandler> assetHandler)
    : camera(camera), assetHandler(assetHandler)
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
    // Initialization of UI elements could go here if needed
    //assetHandler->LoadTexture("menuBackground", "path/to/texture.png");
    //assetHandler->LoadFont("Arial", 24, "path/to/font.ttf");
}

void UIManager::Update()
{
    float deltaTime = Time::DeltaTime();

    // Update menu selection logic
    UpdateMenuSelection();


}

void UIManager::Render(SDL_Renderer* renderer)
{
    // Render each menu option
    for (size_t i = 0; i < menuOptions.size(); ++i)
    {
        const MenuOption& option = menuOptions[i];
        SDL_Rect rect = option.bounds;

        // If the option is selected, highlight it (you could use a color or border change)
        if (i == selectedOption)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Highlight color (red)
            SDL_RenderFillRect(renderer, &rect);
        }

        // Render the text of the option
        RenderText(option.text, rect, renderer);
    }
}

void UIManager::HandleInput(InputHandler& inputHandler)
{
	int menuOptionCount = static_cast<int>(menuOptions.size());

    if (inputHandler.GetKeyDown(SDLK_UP))
    {
        selectedOption = (selectedOption - 1 + menuOptionCount) % menuOptionCount;
    }
    else if (inputHandler.GetKeyDown(SDLK_DOWN))
    {
        selectedOption = (selectedOption + 1) % menuOptionCount;
    }

    // If the selected option is confirmed (e.g., Enter)
    if (inputHandler.GetKeyDown(SDLK_RETURN))
    {
        if (!menuOptions.empty())
        {
            menuOptions[selectedOption].action();
        }
    }
}

void UIManager::AddMenuOption(const std::string& text, std::function<void()> action)
{
    // Calculate a basic bounding box for the menu option
    SDL_Rect bounds = { 100, 100 + static_cast<int>(menuOptions.size()) * 50, 200, 40 };
    menuOptions.push_back({ text, action, bounds });
}

void UIManager::RenderText(const std::string& text, const SDL_Rect& rect, SDL_Renderer* renderer)
{
    //Use AssetHandler to load font and render text
    SDL_Color textColor = { 255, 0, 255, 255 }; //purple example

    SDL_Texture* texture = assetHandler->GetFontTexture("assets/Fonts/arial.ttf", 24, text, textColor);

    if (texture)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture); //Cleanup texture after rendering
    }
    else
    {
        return;
    }
        
}

void UIManager::UpdateMenuSelection()
{
    // Logic for managing selected menu option highlight could go here
    // (This can be expanded with animations, sounds, etc. in the future)
}
