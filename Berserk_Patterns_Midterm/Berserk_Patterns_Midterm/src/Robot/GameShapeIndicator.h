#pragma once

#include "../EntityManager/Entity.h"

class GameShapeIndicator : public Entity
{
public:
	GameShapeIndicator();
	Model* eucherGameModel;
	Model* explodingKittensGameModel;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
};

