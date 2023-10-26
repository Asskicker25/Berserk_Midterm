#pragma once

#include "../EntityManager/Entity.h"
#include "../Maze/MazeColliderSize.h"
#include "MazePathFinding.h"

class Maze : public Entity
{
private:
	Model* mazeModel;
	MazePathFinding pathFinding;

	std::vector<ColliderSize> collidersData;

public:
	static const int MAZE_CELL_SIZE = 10;
	static const int MAZE_X_SIZE = 10;
	static const int MAZE_Y_SIZE = 6;

	std::vector<PhysicsObject*> colliders;

	Maze();
	bool RayCastMazeWall(glm::vec3& origin, glm::vec3& direction, float rayDist);
	bool GetPathPoints(glm::vec2& startPoint, glm::vec2& endPoint, std::vector<glm::vec2>& pathPoints);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

