#pragma once

#include "Robot.h"
#include "../EntityManager/EntityManager.h"
#include "../Maze/Maze.h"

class RobotsManager 
{
private:

	//Pointer implementation used to abstract private calculations
	class PIMPL;
	PIMPL* pimpl;

public:
	//Forward declaration of the enum RobotState 
	//Has the game states for each question
	enum RobotsState;

	RobotsManager();

	//Assigning entity mangagert and maze to the robots that have been created
	void AssignEntityManager(EntityManager& entityManager);
	void SetMaze(Maze* maze);
	
	//Called to load the robots in their respective position 
	void LoadRobots();

	void Update(float deltaTime);

};

