#pragma once

#include <Graphics/Renderer.h>
#include <Physics/PhysicsEngine.h>

class Entity
{
public:
	virtual ~Entity() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) = 0;

	virtual void RemoveFromRenderer(Renderer& renderer) = 0;
	virtual void RemoveFromPhysics(PhysicsEngine& physicsEngine) = 0;
};

