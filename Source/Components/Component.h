#pragma once

#include <memory>

class GameObject;

class Component
{
	friend class GameObject;

public:
	Component(GameObject* _gameObject);
	virtual ~Component() = 0 { gameObject = nullptr; };

	/// @brief Gets the GameObject that this component is attached to
	inline GameObject* GetGameObject() const { return gameObject; }

	/// @brief Gets the unique ID of this component, used to identify the component
	/// during RemoveComponent calls
	inline const unsigned int GetComponentID() const { return componentID; }

protected:
	bool canHaveMultiple;

private:
	GameObject* gameObject;
	unsigned int componentID;
	static unsigned int componentCounter;
};

