#pragma once

#include "RobotBase.h"
#include "../Maze/Maze.h"
#include "GameShapeIndicator.h"

//Enum denoting the current game assigned to the robot
enum RobotGame
{
	None,
	Euchre,
	ExplodingKittens
};

class Robot : public RobotBase
{
private:
	//Pointer to the friend robot of this robot object
	Robot* friendRobot;
	
	//Pointer to the robot that this robot is currently moving towards
	Robot* destinationRobot;

	Maze* maze;

	int currentFriendValue;
	int closeMinDistance = 3.0f;
	int currentPathIndex = 0;

	float positionReachedThreshold = 1.0f;

	//The assigned game (Eucher / Exploding Kitten) 
	RobotGame currentGame;

	//Current path points that the robot is using to move to the destination
	std::vector<glm::vec2> pathPoints;

	glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f);

	//The offset of the game indicator
	//Sphere : Eucher
	//Square : Exploding kitten
	glm::vec3 indicatorOffset = glm::vec3(0.0f, 2.5f, 1.5f);

	float timeStep = 0;
	float timerInterval = 1.0f;

	//Function to update the position of the indicator along with the robot
	void UpdateIndicatorPosition();

public:
	glm::vec3 robotInitSpawnPos = glm::vec3(0.0f, 0.0f, 0.0f);

	GameShapeIndicator* gameShape =  nullptr;

	bool isReachedDestination = false;
	bool isGiftGiven = false;
	bool isAlone = false;

	Robot();
	
	//Returns current friend value
	const int& GetFriendValue();

	//Sets a robot as best friend for this robot object
	void SetBestFriend(Robot* robot, int& friendValue);

	//Getters for best friend robot and the current destination robot
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

