#include "RobotsManager.h"
#include "AbstractFactory/RobotFactory.h"
#include "../Utilities/Random.h"
#include "../Maze/Maze.h"

class RobotsManager::PIMPL
{
public:
	static const int NUM_OF_ROBOTS = 10;
	static const int ORIGIN_OFFSET = 5;
	static constexpr float ROBOT_SCALE = 0.025f;

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

		int randomX = GetRandomIntNumber(0, Maze::MAZE_X_SIZE - 1);
		int randomY = GetRandomIntNumber(0, Maze::MAZE_Y_SIZE - 1);

		robot->robotModel->transform.SetPosition(
			glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * randomX),
				ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * randomY),
				1.0f)
		);
		robot->robotModel->transform.SetScale(glm::vec3(ROBOT_SCALE));

		robot->robotModel->modelId = std::string("Robot " + std::to_string(i));

		entityManager->AddEntity("Robot " + std::to_string(i), robot);

		listOfRobots.push_back(robot);

		robot = nullptr;
	}

	delete robot;
}
