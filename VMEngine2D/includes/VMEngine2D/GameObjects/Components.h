#pragma once

class GameObject;

class Components {
public:

	Components(GameObject* OwnerToAttatch);

	virtual ~Components();

	//contain all logic for components
	virtual void Update(){}

	//other classes to test the owner
	GameObject* GetOwner() const { return OwnerObject; }

protected:
	//store owner object
	GameObject* OwnerObject;
};
