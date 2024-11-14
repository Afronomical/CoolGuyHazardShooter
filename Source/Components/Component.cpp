#include "Component.h"

unsigned int Component::componentCounter = 0;

Component::Component(GameObject* _gameObject) : gameObject(_gameObject), componentID(componentCounter++), 
												canHaveMultiple(false), isActive(true)
{
}
