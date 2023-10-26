#pragma once

#include "../EntityManager/Entity.h"

class Maze : public Entity
{
private:
	Model* mazeModel;

public:
	static const int MAZE_CELL_SIZE = 10;
	static const int MAZE_X_SIZE = 10;
	static const int MAZE_Y_SIZE = 6;

	Maze();

	// Inherited via Entity
	void Start() override;
	void Update() override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

