#pragma once

#include "Robot.h"
#include "../EntityManager/EntityManager.h"
#include "../Maze/Maze.h"

class RobotsManager 
{
private:

	class PIMPL;
	PIMPL* pimpl;

	float timeStep = 0;

	float intervalBetweenStates = 2.0f;


public:
	enum RobotsState;

	RobotsState robotsState;

	RobotsManager();

	void AssignEntityManager(EntityManager& entityManager);
	void SetMaze(Maze* maze);
	void LoadRobots();
	void SetRobotsState(RobotsState robotsState);

	void Update(float deltaTime);

	void CheckIfAllFriendsFound(float deltaTime);
	void CheckIfAllRobotsGameOver(float deltaTime);
	void CheckIfGiftGiven(float deltaTime);
	void CheckIfAllRobotsAreAlone(float deltaTime);

};

