#pragma once
#include "SDL.h"
#include <functional>
#include <unordered_map>

enum ButtonState
{
	None,
	Pressed,
	Held,
	Released
};

struct BindData
{
	std::function<void()> action;
	ButtonState buttonState;
	BindData() : action(nullptr), buttonState(None) {};
	BindData(std::function<void()> _action, ButtonState _buttonState) : action(_action), buttonState(_buttonState) {};
};

struct Mouse
{
	//Vector2 position;  INFO: kept out as V2 not implemented yet 
	float width;
	float height;

	//Mouse(); // : position(Vector2(0, 0)), width(0), height(0) {};
};
class InputHandler
{
private:
#pragma region Properties
	static std::unordered_map<Sint32, BindData> keyBoardActions;   //did not like sdl keycode when binding so changed it to it's int value - Sint32 

	static std::unordered_map<Uint32, BindData> mouseButtonActions;

	static std::function<void(int, int)> mouseMovementAction;

	static const Uint8* currentKeyState;

	static Uint8* previousKeyState;

	static int keyLength;

	static const Uint32 currentMouseState;

	static Uint32 previousMouseState;

	static Mouse mouse;

	static InputHandler* _instance;
#pragma endregion

public: 

#pragma region Methods
	static InputHandler* instance() { return _instance != nullptr ? _instance : _instance = new InputHandler(); }

	static bool Initialise();

	static void BindKeyToAction(SDL_Keycode key, BindData data);

	static void BindMouseButtonToAction(Uint32 button, BindData data);

	static void BindMouseMovementToAction(std::function<void(int, int)> action);

	static bool GetKey(SDL_Keycode key);

	static bool GetKeyDown(SDL_Keycode key);

	static bool GetKeyUp(SDL_Keycode key);

	static bool GetMouseButton(Uint32 button);

	static bool GetMouseButtonDown(Uint32 button);

	static bool GetMouseButtonUp(Uint32 button);

	static const Mouse& GetMouse();

	static void HandleInputs();

	static void ClearAllBindings();

	static void ClearKeyBindings();

	static void ClearKeyBinding(Sint32 key);

	static void ClearMouseBindings();

	static void ClearMouseBinding(Uint32 button);

	static void ClearMouseMovementBinding();

	static void Clean();

	


	
	
};

