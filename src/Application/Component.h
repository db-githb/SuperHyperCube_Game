#pragma once

class ObjectNode;
class Component
{
	
public:

	ObjectNode* gameObject;

	inline void SetGameObject(ObjectNode* object) { gameObject = object; };
	//virtual void Update(float ms) = 0;
	
};
