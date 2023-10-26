#pragma once

#include "../EntityManager/Entity.h"

class Maze : public Entity
{
private:
	Model* mazeModel;

public:
	Maze();

	// Inherited via Entity
	void Start() override;
	void Update() override;
	void AddToRenderer(Renderer& renderer, Shader* shader) override;
	void AddToPhysics(PhysicsEngine& physicsEngine) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
};

