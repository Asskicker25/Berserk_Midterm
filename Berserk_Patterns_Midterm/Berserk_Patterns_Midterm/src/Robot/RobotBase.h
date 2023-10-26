#pragma once

#include "../EntityManager/Entity.h"

class RobotBase : public Entity
{
	// Inherited via Entity
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void AddToRenderer(Renderer& renderer, Shader* shader) = 0;
	virtual void AddToPhysics(PhysicsEngine& physicsEngine) = 0;
	virtual void RemoveFromRenderer(Renderer& renderer) = 0;
	virtual void RemoveFromPhysics(PhysicsEngine& physicsEngine) = 0;
};

