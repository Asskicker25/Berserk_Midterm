#pragma once

#include "../EntityManager/Entity.h"
#include "../Maze/MazeColliderSize.h"

class Maze : public Entity
{
private:
	Model* mazeModel;

	std::vector<ColliderSize> collidersData;

public:
	static const int MAZE_CELL_SIZE = 10;
	static const int MAZE_X_SIZE = 10;
	static const int MAZE_Y_SIZE = 6;

	std::vector<PhysicsObject*> colliders;

	Maze();

	// Inherited via Entity
	void Start() override;
	void Update() override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

