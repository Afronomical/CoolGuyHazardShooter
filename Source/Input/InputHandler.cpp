#include "InputHandler.h"
#include <iostream>"

std::unordered_map<Sint32, BindData> InputHandler::keyBoardActions;
std::unordered_map<Uint32, BindData> InputHandler::mouseButtonActions;
std::function<void(int, int)> InputHandler::mouseMovementAction;
const Uint8* InputHandler::currentKeyState = nullptr;
Uint8* InputHandler::previousKeyState = nullptr;
int InputHandler::keyLength = 0;
const Uint32 InputHandler::currentMouseState = 0;
Uint32 InputHandler::previousMouseState = 0;
Mouse InputHandler::mouse;

bool InputHandler::Initialise()
{
	if (SDL_Init(SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	currentKeyState = SDL_GetKeyboardState(&keyLength);
	if (!currentKeyState)
	{
		std::cout << "failed to get keyboard state" << std::endl;
		return false;
	}

	previousKeyState = new Uint8[keyLength];
	if (!previousKeyState)
	{
		std::cout << "failed to get memory for previous key state" << std::endl;
		return false;

	}
	memcpy(previousKeyState, currentKeyState, keyLength);
	
	std::cout << "InputHandler initialised" << std::endl;
	return true;
}

void InputHandler::BindKeyToAction(SDL_Keycode key, BindData data)
{
	keyBoardActions[key] = data;
	std::cout << "Key bound to action" << std::endl;
	//output key info 
}

void InputHandler::BindMouseButtonToAction(Uint32 button, BindData data)
{
	mouseButtonActions[button] = data;
}

void InputHandler::BindMouseMovementToAction(std::function<void(int, int)> action)
{
	mouseMovementAction = action; 
}

bool InputHandler::GetKey(SDL_Keycode key)
{
	if (currentKeyState[key] == 1)
		return true;
	else
	return false;
}

bool InputHandler::GetKeyDown(SDL_Keycode key)
{
	if (currentKeyState[key] == 1 && previousKeyState[key] == 0)
		return true;
	else
		return false;
}

bool InputHandler::GetKeyUp(SDL_Keycode key)
{
	if (currentKeyState[key] == 0 && previousKeyState[key] == 1)
		return true;
	else
	return false;
}

bool InputHandler::GetMouseButton(Uint32 button)
{
	if (currentMouseState & SDL_BUTTON(button))
		return true;
	else
		return false;
	
}

bool InputHandler::GetMouseButtonDown(Uint32 button)
{
	if (currentMouseState & SDL_BUTTON(button) && !(previousMouseState & SDL_BUTTON(button)))
		return true;
	else
		return false;
}

bool InputHandler::GetMouseButtonUp(Uint32 button)
{
	if (!(currentMouseState & SDL_BUTTON(button)) && previousMouseState & SDL_BUTTON(button))
		return true;
	else
		return false;
}

const Mouse& InputHandler::GetMouse()
{
	return mouse;
	// TODO: insert return statement here
}

void InputHandler::HandleInputs()
{
	std::cout << "Handling inputs" << std::endl;
	memcpy(previousKeyState, currentKeyState, keyLength);

	previousMouseState = currentMouseState;

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (keyBoardActions.find(event.key.keysym.sym) != keyBoardActions.end())
			{
				keyBoardActions[event.key.keysym.sym].action();
			}
			break;
		case SDL_KEYUP:
			if (keyBoardActions.find(event.key.keysym.sym) != keyBoardActions.end())
			{
				keyBoardActions[event.key.keysym.sym].action();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mouseButtonActions.find(event.button.button) != mouseButtonActions.end())
			{
				mouseButtonActions[event.button.button].action();
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (mouseButtonActions.find(event.button.button) != mouseButtonActions.end())
			{
				mouseButtonActions[event.button.button].action();
			}
			break;
		case SDL_MOUSEMOTION:
			//mouse.x = event.motion.x;
			//mouse.y = event.motion.y;
			if (mouseMovementAction != nullptr)
			{
				mouseMovementAction(event.motion.xrel, event.motion.yrel);
			}
			break;
		default:
			break;
		}
	}

}

void InputHandler::ClearAllBindings()
{
	keyBoardActions.clear();
	mouseButtonActions.clear();
	mouseMovementAction = nullptr;
}

void InputHandler::ClearKeyBindings()
{
	keyBoardActions.clear();
}

void InputHandler::ClearKeyBinding(Sint32 key)
{
	//finds specified key and clears it from the map
	keyBoardActions.erase(key);
	
}

void InputHandler::ClearMouseBindings()
{
	mouseButtonActions.clear();
}

void InputHandler::ClearMouseBinding(Uint32 button)
{
	//finds specified mouse button and clears it from the map
	mouseButtonActions.erase(button);
}

void InputHandler::ClearMouseMovementBinding()
{
	mouseMovementAction = nullptr;
}

void InputHandler::Clean()
{
	delete[] previousKeyState;
	previousKeyState = nullptr;
}
