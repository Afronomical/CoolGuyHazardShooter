#pragma once

#include <memory>
#include <queue>
#include <vector>

class Collider;
class Component;
class Transform;

class GameObject
{
public:
	class Handler
	{
	public:
		static void Start();
		static void Update(float deltaTime);
		static void LateUpdate(float deltaTime);
		static void Draw();

		static void Clean();

		static void RegisterGameObject(GameObject* gameObject);
		static void UnregisterGameObject(GameObject* gameObject);

		static void ProcessDeletionQueue();

	private:
		static std::vector<GameObject*> gameObjects;
		static std::queue<GameObject*> deletionQueue;
	};

public:
	GameObject();
	virtual ~GameObject() = 0 {};

	void Destroy();

	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw() {};

	virtual void OnCollisionEnter(Collider* other) {};
	virtual void OnCollisionStay(Collider* other) {};
	virtual void OnCollisionExit(Collider* other) {};

	virtual void OnTriggerEnter(Collider* other) {};
	virtual void OnTriggerStay(Collider* other) {};
	virtual void OnTriggerExit(Collider* other) {};

	virtual void OnDestroy() {};

	template<class T>
	std::weak_ptr<T> GetComponent();

	template<class T, typename... Args>
	std::weak_ptr<T> AddComponent(Args&&... args);

	template<class T>
	bool RemoveComponent(unsigned int componentID);

public:
	std::weak_ptr<Transform> transform;

private:
	std::vector<std::shared_ptr<Component>> components;
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