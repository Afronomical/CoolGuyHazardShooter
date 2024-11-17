#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "../Camera/Camera.h"
#include "../Collision/Collider.h"

class Component;
class Transform;

class GameObject
{
public:
	class Handler
	{
	public:
		/// @brief Utility function used to call the Start function for all game objects
		static void Start();

		/// @brief Utility function used to call the Update function for all game objects
		/// @param deltaTime : The time between frames
		static void Update(float deltaTime);

		/// @brief Utility function used to call the LateUpdate function for all game objects
		/// @param deltaTime : The time between frames
		static void LateUpdate(float deltaTime);

		/// @brief Utility function used to call the Draw function for all game objects
		static void Draw();

		/// @brief Utility function used to clean up all game objects
		static void Clean();

		/// @brief Used to set the camera for the handler so it can be used to work out
		/// whether the game object is in view or not
		static inline void SetCamera(std::shared_ptr<Camera> _camera) { camera = _camera; }

		/// @brief Used to register a game object with the handler
		/// @param gameObject : The game object to register
		static void RegisterGameObject(GameObject* gameObject);

		/// @brief Used to unregister a game object with the handler, this will queue the
		/// game object for deletion at the end of the frame
		/// @param gameObject : The game object to unregister
		static void UnregisterGameObject(GameObject* gameObject);

		/// @brief Used to process the deletion queue, this will delete all game objects
		/// that have been queued for deletion
		static void ProcessDeletionQueue();

	private:
		static std::vector<GameObject*> gameObjects;
		static std::queue<GameObject*> deletionQueue;
		
		static std::weak_ptr<Camera> camera;

	private:
		Handler() = delete;
		~Handler() = delete;
		Handler(const Handler&) = delete;
		Handler& operator=(const Handler&) = delete;
	};

public:
	GameObject();
	virtual ~GameObject() = 0 {};

	/// @brief Used to destroy the game object
	void Destroy();

	inline void SetIsActive(bool _isActive) { isActive = _isActive; }
	inline bool IsActive() const { return isActive; }

	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw() {};

	virtual void OnCollisionEnter(std::shared_ptr<Collider> other) {};
	virtual void OnCollisionStay(std::shared_ptr<Collider> other) {};
	virtual void OnCollisionExit(std::shared_ptr<Collider> other) {};

	virtual void OnTriggerEnter(std::shared_ptr<Collider> other) {};
	virtual void OnTriggerStay(std::shared_ptr<Collider> other) {};
	virtual void OnTriggerExit(std::shared_ptr<Collider> other) {};

	/// @brief Event that is called when the game object is destroyed
	virtual void OnDestroy() {};

	template<class T>
	std::weak_ptr<T> GetComponent();

	template<class T, typename... Args>
	std::weak_ptr<T> AddComponent(Args&&... args);

	template<class T>
	bool RemoveComponent(unsigned int componentID);

public:
	std::weak_ptr<Transform> transform;

protected:
	bool isActive;
	bool alwaysUpdate; // INFO: If true, the game object will always update regardless of whether it is in view or not

private:
	std::vector<std::shared_ptr<Component>> components;
	bool isInView; // INFO: If true, the game object is in view of the camera and should be updated and drawn
};

template<class T>
inline std::weak_ptr<T> GameObject::GetComponent()
{
	// INFO: Loop through all components, casting each to the desired type
	//       if the cast is successful, return the component, otherwise return nullptr
	for (auto& component : components)
	{
		std::weak_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);

		if (!castedComponent.expired())
			return castedComponent;
	}

	return std::weak_ptr<T>();
}

template<class T, typename ...Args>
inline std::weak_ptr<T> GameObject::AddComponent(Args && ...args)
{
	// INFO: Ensure the component being added derives from the Component class
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

	// INFO: Check to see if the component already exists
	std::weak_ptr<T> existingComponent = GetComponent<T>();

	// INFO: Return if the component already exists and we can only have one
	if (!existingComponent.expired() && existingComponent.lock()->canHaveMultiple)
		return existingComponent;

	// INFO: Create the component and add it to the components vector
	components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));

	// INFO: If the component is a collider, register it with the collider handler
	if (std::dynamic_pointer_cast<Collider>(components.back()))
		Collider::Handler::RegisterCollider(std::dynamic_pointer_cast<Collider>(components.back()));

	// INFO: Return the newly created component
	return std::dynamic_pointer_cast<T>(components.back());
}

template<class T>
inline bool GameObject::RemoveComponent(unsigned int componentID)
{
	// INFO: Loop through all components, if the component ID matches the desired ID, delete the component
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		T* castedComponent = dynamic_cast<T*>(it->get());

		// INFO: Check to see if the component is valid
		if (castedComponent != nullptr)
		{
			// INFO: Continue searching if the component ID does not match the desired ID
			if (castedComponent->GetComponentID() != componentID)
				continue;

			// INFO: Remove the component (Using smart pointers so no need to delete)
			components.erase(it);

			return true;
		}
	}

	return false;
}