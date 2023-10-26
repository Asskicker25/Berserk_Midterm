#include "RobotsManager.h"
#include "AbstractFactory/RobotFactory.h"

class RobotsManager::PIMPL
{
public:
	static const int NUM_OF_ROBOTS = 9;

	std::vector<Robot*> listOfRobots;

	RobotFactory robotFactory;
	EntityManager* entityManager;

	void LoadRobots();
};

RobotsManager::RobotsManager() : pimpl { new PIMPL()}
{
}

void RobotsManager::AssignEntityManager(EntityManager& entityManager)
{
	pimpl->entityManager = &entityManager;
}

void RobotsManager::LoadRobots()
{
	pimpl->LoadRobots();
}

void RobotsManager::PIMPL::LoadRobots()
{
	Robot* robot;
	for (int i = 0; i < NUM_OF_ROBOTS; i++)
	{
		robot = (Robot*)robotFactory.CreateRobot();

		robot->robotModel->transform.SetPosition(glm::vec3(5.0f + (5.0f * i), 10.0f + (5.0f * i), 5.0f));
		robot->robotModel->transform.SetScale(glm::vec3(0.05f));

		robot->robotModel->modelId = std::string("Robot " + std::to_string(i));

		entityManager->AddEntity("Robot " + std::to_string(i), robot);

		listOfRobots.push_back(robot);

		robot = nullptr;
	}

	delete robot;
}
