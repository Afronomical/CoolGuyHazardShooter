#include "GameObject.h"

#include "../Components/Transform.h"
#include "../Debugging/MemoryLeakDetector.h"

#pragma region StaticHandlerMembers
std::vector<GameObject*> GameObject::Handler::gameObjects;
std::queue<GameObject*> GameObject::Handler::deletionQueue;
#pragma endregion StaticHandlerMembers

#pragma region HandlerMethods
void GameObject::Handler::Start()
{
	// INFO: Loop through all game objects and call their Start function if they are active
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsActive())
			gameObject->Start();
	}
}

void GameObject::Handler::Update(float deltaTime)
{
	// INFO: Loop through all game objects and call their Update function if they are active
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsActive())
			gameObject->Update(deltaTime);
	}
}

void GameObject::Handler::LateUpdate(float deltaTime)
{
	// INFO: Loop through all game objects and call their LateUpdate function if they are active
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsActive())
			gameObject->LateUpdate(deltaTime);
	}
}

void GameObject::Handler::Draw()
{
	// INFO: Loop through all game objects and call their Draw function if they are active
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsActive())
			gameObject->Draw();
	}
}

void GameObject::Handler::Clean()
{
	// INFO: Loop through all game objects and delete all of their components
	//       then delete the game object itself
	for (auto& gameObject : gameObjects)
	{
		// INFO: Clear the game objects components vector
		gameObject->components.clear();

		delete gameObject;
	}

	// INFO: Clear the game objects vector
	gameObjects.clear();
}

void GameObject::Handler::RegisterGameObject(GameObject* gameObject)
{
	// INFO: Add the game object to the game objects vector
	gameObjects.push_back(gameObject);
}

void GameObject::Handler::UnregisterGameObject(GameObject* gameObject)
{
	// INFO: Add the game object to the deletion queue
	deletionQueue.push(gameObject);
}

void GameObject::Handler::ProcessDeletionQueue()
{
	// INFO: Loop through all game objects in the deletion queue and delete them
	while (!deletionQueue.empty())
	{
		GameObject* gameObject = deletionQueue.front();
		deletionQueue.pop();

		// INFO: Clear the game objects components vector
		gameObject->components.clear();

		// INFO: Delete the game object
		delete gameObject;
	}

	// INFO: Iterator over the game objects vector and remove any nullptrs
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		// INFO: Continue if the game object is not nullptr, otherwise remove it
		if (*it != nullptr)
			continue;

		gameObjects.erase(it);
	}
}
#pragma endregion HandlerMethods

#pragma region GameObjectMethods
GameObject::GameObject() : isActive(true), components()
{
	// INFO: Register the game object with the handler
	GameObject::Handler::RegisterGameObject(this);

	// INFO: Add a transform component to the game object
	transform = AddComponent<Transform>(this);
}

void GameObject::Destroy()
{
	// INFO: Call OnDestroy for last minute user defined logic
	OnDestroy();

	// INFO: Unregister the game object ready for deletion at the end of the frame
	Handler::UnregisterGameObject(this);
}
#pragma endregion GameObjectMethods
