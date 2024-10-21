#pragma once

class GameObject;

class Component
{
	friend class GameObject;

public:
	Component(GameObject* _gameObject);
	virtual ~Component() = 0 { gameObject = nullptr; };

	inline GameObject* GetGameObject() const { return gameObject; }
	inline const unsigned int GetComponentID() const { return componentID; }

protected:
	bool canHaveMultiple;

private:
	GameObject* gameObject;
	unsigned int componentID;
	static unsigned int componentCounter;
};

