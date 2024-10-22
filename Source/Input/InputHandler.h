#pragma once

#include <SDL.h>

#include <functional>
#include <unordered_map>

#include "Mouse.h"

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

class InputHandler
{
public: 
	static bool Initialise();

	static inline void BindKeyToAction(SDL_Keycode key, BindData data) { keyboardActions[key] = data; }
	static inline void BindMouseButtonToAction(Uint32 button, BindData data) { mouseButtonActions[button] = data; }
	static inline void BindMouseMovementToAction(std::function<void(int, int)> action) { mouseMovementAction = action; }

	static inline bool GetKey(SDL_Keycode key) { return currentKeyState[key]; }
	static inline bool GetKeyDown(SDL_Keycode key) { return currentKeyState[key] && !previousKeyState[key]; }
	static inline bool GetKeyUp(SDL_Keycode key) { return !currentKeyState[key] && previousKeyState[key]; }

	static inline bool GetMouseButton(Uint32 button) { return currentMouseState & SDL_BUTTON(button); }
	static inline bool GetMouseButtonDown(Uint32 button) { return (currentMouseState & SDL_BUTTON(button)) && !(previousMouseState & SDL_BUTTON(button)); }
	static inline bool GetMouseButtonUp(Uint32 button) { return !(currentMouseState & SDL_BUTTON(button)) && (previousMouseState & SDL_BUTTON(button)); }

	static inline const Mouse& GetMouse() { return mouse; }

	static void HandleInputs();

	static void ClearAllBindings();

	static inline void ClearKeyBindings() { keyboardActions.clear(); }
	static inline void ClearKeyBinding(SDL_Keycode key) { keyboardActions.erase(key); }

	static inline void ClearMouseBindings() { mouseButtonActions.clear(); }
	static inline void ClearMouseBinding(Uint32 button) { mouseButtonActions.erase(button); }

	static inline void ClearMouseMovementBinding() { mouseMovementAction = nullptr; }

	static void Clean();

private:
	static std::unordered_map<SDL_Keycode, BindData> keyboardActions;
	static std::unordered_map<Uint32, BindData> mouseButtonActions;

	static std::function<void(int, int)> mouseMovementAction;

	static const Uint8* currentKeyState;
	static Uint8* previousKeyState;
	static int keyLength;

	static const Uint32 currentMouseState;
	static Uint32 previousMouseState;
	static Mouse mouse;
};

