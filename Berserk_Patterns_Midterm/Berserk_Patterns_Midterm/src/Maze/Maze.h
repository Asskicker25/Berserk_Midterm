#pragma once

#include "../EntityManager/Entity.h"
#include "../Maze/MazeColliderSize.h"
#include "MazePathFinding.h"

class Maze : public Entity
{
private:
	//Model of the maze
	Model* mazeModel;

	//Instance of the MazePathFinding class that handles the path fincding logic
	MazePathFinding pathFinding;

	//A list of colliderdata through which I create and scale a collider to match the extents of walls
	std::vector<ColliderSize> collidersData;

public:
	//Details of the maze 
	static const int MAZE_CELL_SIZE = 10;
	static const int MAZE_X_SIZE = 10;
	static const int MAZE_Y_SIZE = 6;

	//List of the colliders that have been added to the walls
	std::vector<PhysicsObject*> colliders;

	Maze();

	//Returns true if a raycast from a point with direction hits the walls of the maze
	bool RayCastMazeWall(glm::vec3& origin, glm::vec3& direction, float rayDist);

	//Returns true if a path has been found from a starting point to ending point
	//Returns a output referenced pathPoints that have the points needed to naviagate from start to end
	bool GetPathPoints(glm::vec2& startPoint, glm::vec2& endPoint, std::vector<glm::vec2>& pathPoints);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

