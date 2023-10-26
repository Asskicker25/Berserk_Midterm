#pragma once

#include "RobotBase.h"
#include "../Maze/Maze.h"

class Robot : public RobotBase
{
private:
	Robot* friendRobot;
	Robot* destinationRobot;

	Maze* maze;

	int currentFriendValue;
	int closeMinDistance = 2.0f;
	int currentPathIndex = 0;

	float positionReachedThreshold = 1.0f;

	glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
	std::vector<glm::vec2> pathPoints;

public:
	Robot();

	const int& GetFriendValue();
	void SetBestFriend(Robot* robot, int& friendValue);
	Robot* GetBestFriend();

	void GetPathPoints(std::vector<glm::vec2>& pathPoints);

	void SetMaze(Maze* maze);
	void MoveTowardsRobot(Robot* robot);
	void MoveTowardsFriend();

	bool IsDestinationReached();

	void ChangeColor(glm::vec3 color);
	void UpdateVelocity(float deltaTime);

	// Inherited via RobotBase
	void Start() override;
	void Update(float deltaTime) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

