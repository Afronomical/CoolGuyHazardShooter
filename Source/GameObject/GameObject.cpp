#include "GameObject.h"

#include "../Components/Transform.h"
#include "../Debugging/MemoryLeakDetector.h"

#pragma region StaticHandlerMembers
std::vector<GameObject*> GameObject::Handler::gameObjects;
std::queue<GameObject*> GameObject::Handler::deletionQueue;
std::weak_ptr<Camera> GameObject::Handler::camera;
TileLayer* GameObject::Handler::mapGameObjectLayer;
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
		// INFO: If the object isn't active skip it
		if (!gameObject->IsActive())
			continue;

		// INFO: Perform a check to see if the game object is in view of the camera if alwaysUpdate is false
		if (!gameObject->alwaysUpdate)
		{
			std::shared_ptr<Transform> transform = gameObject->transform.lock();
			SDL_Rect rect = { transform->position.X, transform->position.Y, transform->size.X, transform->size.Y };

			gameObject->isInView = camera.lock()->IsInView(rect);
		}

		// INFO: If the game object is in view or alwaysUpdate is true then update the game object
		if (gameObject->isInView || gameObject->alwaysUpdate)
			gameObject->Update(deltaTime);
	}
}

void GameObject::Handler::LateUpdate(float deltaTime)
{
	// INFO: Loop through all game objects and call their LateUpdate function if they are active
	for (auto& gameObject : gameObjects)
	{
		// INFO: If the object isn't active skip it
		if (!gameObject->IsActive())
			continue;

		// INFO: If the game object is in view or alwaysUpdate is true then call LateUpdate
		if (gameObject->isInView || gameObject->alwaysUpdate)
			gameObject->LateUpdate(deltaTime);
	}
}

void GameObject::Handler::Draw()
{
	// INFO: Loop through all game objects and call their Draw function if they are active
	for (auto& gameObject : gameObjects)
	{
		// INFO: If the object isn't active skip it
		if (!gameObject->IsActive())
			continue;

		// INFO: If the game object is in view or alwaysUpdate is true then draw the game object
		if (gameObject->isInView || gameObject->alwaysUpdate)
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

void GameObject::Handler::SetMapGameObjectLayer(TileLayer* gameObjectLayer)
{
	// INFO: Unregister all game objects from the previous layer
	for (auto& gameObject : gameObjects)
		UnregisterGameObject(gameObject);

	// INFO: Set the new game object layer
	mapGameObjectLayer = gameObjectLayer;

	// INFO: Instantiate game objects from the map
	InstantiateGameObjectsFromMap();
}

void GameObject::Handler::InstantiateGameObjectsFromMap()
{
	int tileSize = mapGameObjectLayer->GetTileSize();
	int numRows = mapGameObjectLayer->GetNumRows();
	int numColumns = mapGameObjectLayer->GetNumColumns();

	std::vector<std::vector<int>> tilemap = mapGameObjectLayer->GetTilemap();

	// INFO: Loop through the tilemap and instantiate game objects based on the tile IDs
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numColumns; j++)
		{
			// INFO: If the tile ID is 0 then skip it
			if (tilemap[i][j] == 0)
				continue;

			switch (tilemap[i][j])
			{
				// INSTANTIATE GAME OBJECTS HERE

			default:
				break;
			}

		}
	}
}
#pragma endregion HandlerMethods

#pragma region GameObjectMethods
GameObject::GameObject() : isActive(true), alwaysUpdate(false), components(), isInView(false)
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
