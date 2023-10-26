#pragma once

#include "RobotBase.h"
#include "../Maze/Maze.h"
#include "GameShapeIndicator.h"

enum RobotGame
{
	None,
	Euchre,
	ExplodingKittens
};

class Robot : public RobotBase
{
private:
	Robot* friendRobot;
	Robot* destinationRobot;

	Maze* maze;

	int currentFriendValue;
	int closeMinDistance = 3.0f;
	int currentPathIndex = 0;

	float positionReachedThreshold = 1.0f;

	RobotGame currentGame;

	std::vector<glm::vec2> pathPoints;

	glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 indicatorOffset = glm::vec3(0.0f, 2.5f, 0.0f);

	float timeStep = 0;
	float timerInterval = 1.0f;

	void UpdateIndicatorPosition();

public:
	glm::vec3 robotInitSpawnPos = glm::vec3(0.0f, 0.0f, 0.0f);

	Robot* holderForStartPos;
	GameShapeIndicator* gameShape =  nullptr;

	bool isReachedDestination = false;
	bool isGiftGiven = false;
	bool isAlone = false;

	Robot();

	const int& GetFriendValue();
	void SetBestFriend(Robot* robot, int& friendValue);
	Robot* GetBestFriend();
	Robot* GetDestinationRobot();

	void GetPathPoints(std::vector<glm::vec2>& pathPoints);

	void SetMaze(Maze* maze);
	void MoveTowardsRobot(Robot* robot);
	void MoveTowardsFriend();
	void MoveTowardsStartingPos();

	void SetCurrentGame(RobotGame game);
	void UpdateRobotGiftReceived(Robot* receivedFrom);


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

