#pragma once

#include "Robot.h"
#include "../EntityManager/EntityManager.h"

class RobotsManager 
{
private:

	class PIMPL;
	PIMPL* pimpl;

public:
	RobotsManager();
	void AssignEntityManager(EntityManager& entityManager);
	void LoadRobots();
};

