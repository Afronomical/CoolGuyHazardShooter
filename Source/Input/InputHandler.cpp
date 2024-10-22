#include "InputHandler.h"

//#include "../Debug/Debug.h"

#include "../MemoryLeakDetector/MemoryLeakDetector.h"

std::unordered_map<SDL_Keycode, BindData> InputHandler::keyboardActions;
std::unordered_map<Uint32, BindData> InputHandler::mouseButtonActions;

std::function<void(int, int)> InputHandler::mouseMovementAction;

const Uint8* InputHandler::currentKeyState = nullptr;
Uint8* InputHandler::previousKeyState = nullptr;
int InputHandler::keyLength = 0;

Uint32 InputHandler::currentMouseState = 0;
Uint32 InputHandler::previousMouseState = 0;
Mouse InputHandler::mouse;

bool InputHandler::Initialise()
{
	// INFO: Check to see if everything has been initialised correctly
	bool success = true;

	// INFO: Initialise and Validate Current Key State
	currentKeyState = SDL_GetKeyboardState(&keyLength);

	if (!currentKeyState)
	{
		//Debug::LogError("Failed to initialise currentKeyState!");
		return !success;
	}

	// INFO: Initialise and Validate Previous Key State
	previousKeyState = new Uint8[keyLength];
	memcpy(previousKeyState, currentKeyState, keyLength);

	if (!previousKeyState)
	{
		//Debug::LogError("Failed to initialise previousKeyState!");
		return !success;
	}

	// INFO: Initialise and Validate Current Mouse State
	currentMouseState = SDL_GetMouseState(&mouse.mouseData.x, &mouse.mouseData.y);

	if (!currentMouseState)
	{
		//Debug::LogError("Failed to initialise currentMouseState!");
		return !success;
	}

	// INFO: Initialise and Validate Previous Mouse State
	previousMouseState = currentMouseState;

	if (!previousMouseState)
	{
		//Debug::LogError("Failed to initialise previousMouseState!");
		return !success;
	}

	return success;
}

void InputHandler::HandleInputs()
{
	// INFO: Update Previous Key State so the two can be compared
	memcpy(previousKeyState, currentKeyState, keyLength);

	// INFO: Update Previous Mouse State so the two can be compared
	previousMouseState = currentMouseState;

	// INFO: Update Current Mouse State so the two can be compared
	currentMouseState = SDL_GetMouseState(&mouse.mouseData.x, &mouse.mouseData.y);

	// INFO: Go through keyboardActions and check if any should be triggered
	for (auto& keyboardAction : keyboardActions)
	{
		switch (keyboardAction.second.buttonState)
		{
		case ButtonState::Held:
			if (GetKey(keyboardAction.first))
			{
				keyboardAction.second.action();
			}
			break;
		case ButtonState::Pressed:
			if (GetKeyDown(keyboardAction.first))
			{
				keyboardAction.second.action();
			}
			break;
		case ButtonState::Released:
			if (GetKeyUp(keyboardAction.first))
			{
				keyboardAction.second.action();
			}
			break;
		case ButtonState::None:
		default:
			break;
		}
	}

	// INFO: Go through mouseButtonActions and check if any should be triggered
	for (auto& mouseButtonAction : mouseButtonActions)
	{
		switch (mouseButtonAction.second.buttonState)
		{
		case ButtonState::Held:
			if (GetMouseButton(mouseButtonAction.first))
			{
				mouseButtonAction.second.action();
			}
			break;
		case ButtonState::Pressed:
			if (GetMouseButtonDown(mouseButtonAction.first))
			{
				mouseButtonAction.second.action();
			}
			break;
		case ButtonState::Released:
			if (GetMouseButtonUp(mouseButtonAction.first))
			{
				mouseButtonAction.second.action();
			}
			break;
		case ButtonState::None:
		default:
			break;
		}
	}

	// INFO: Handle any SDL events for generic functionality (e.g. closing the window)
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//Debug::Log("Quit Event Detected!");
			break;
		default:
			break;
		}
	}

}

void InputHandler::ClearAllBindings()
{
	keyboardActions.clear();
	mouseButtonActions.clear();
	mouseMovementAction = nullptr;
}

void InputHandler::Clean()
{
	if (previousKeyState != nullptr)
	{
		delete[] previousKeyState;
		previousKeyState = nullptr;
	}
}
