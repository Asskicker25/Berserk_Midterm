#pragma once

#include "../EntityManager/Entity.h"

class RobotBase : public Entity
{
public :
	Model* robotModel;
	PhysicsObject* robotPhyObj;

	float speed = 15.0f;

	// Inherited via Entity
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void RemoveFromRenderer(Renderer& renderer) = 0;
	virtual void RemoveFromPhysics(PhysicsEngine& physicsEngine) = 0;
	virtual void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) = 0;
};

