#pragma once

#include "Robot.h"
#include "../EntityManager/EntityManager.h"
#include "../Maze/Maze.h"

class RobotsManager 
{
private:

	class PIMPL;
	PIMPL* pimpl;

public:
	enum RobotsState;

	RobotsState robotsState;

	RobotsManager();

	void AssignEntityManager(EntityManager& entityManager);
	void SetMaze(Maze* maze);
	void LoadRobots();
	void SetRobotsState(RobotsState robotsState);
};

