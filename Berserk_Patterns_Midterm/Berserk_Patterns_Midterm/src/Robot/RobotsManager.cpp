#include "RobotsManager.h"
#include "AbstractFactory/RobotFactory.h"
#include "../Utilities/Random.h"
#include "../Maze/Maze.h"

class RobotsManager::PIMPL
{
public:
	static const int NUM_OF_ROBOTS = 2;
	static const int ORIGIN_OFFSET = 5;
	static constexpr float ROBOT_SCALE = 0.025f;

	std::vector<Robot*> listOfRobots;
	Maze* maze;
	//std::vector<Robot*> shuffledListOfRobots;

	RobotFactory robotFactory;
	EntityManager* entityManager;

	void LoadRobots();
	void AssignNewFriends();
};

enum RobotsManager::RobotsState
{
	FINDING_NEW_FRIENDS,
	PLAY_GAME,
	GIVE_GIFTS,
	ALONE
};

RobotsManager::RobotsManager() : pimpl { new PIMPL() }, robotsState { FINDING_NEW_FRIENDS }
{
}

void RobotsManager::AssignEntityManager(EntityManager& entityManager)
{
	pimpl->entityManager = &entityManager;
}

void RobotsManager::LoadRobots()
{
	pimpl->LoadRobots();
	SetRobotsState(FINDING_NEW_FRIENDS);
}

void RobotsManager::SetMaze(Maze* maze)
{
	pimpl->maze = maze;
}

void RobotsManager::SetRobotsState(RobotsState robotsState = FINDING_NEW_FRIENDS)
{
	switch (robotsState)
	{
	case FINDING_NEW_FRIENDS:
		pimpl->AssignNewFriends();
		break;
	case PLAY_GAME:
		break;
	case GIVE_GIFTS:
		break;
	case ALONE:
		break;
	}
}

void RobotsManager::PIMPL::LoadRobots()
{
	Robot* robot;
	for (int i = 0; i < NUM_OF_ROBOTS; i++)
	{
		robot = (Robot*)robotFactory.CreateRobot();

		int randomX = GetRandomIntNumber(0, Maze::MAZE_X_SIZE - 1);
		int randomY = GetRandomIntNumber(0, Maze::MAZE_Y_SIZE - 1);

		if (i == 0)
		{
			robot->robotModel->transform.SetPosition(
				glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * 0),
					ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * 1),
					1.0f)
			);
		}
		else if (i == 1)
		{
			robot->robotModel->transform.SetPosition(
				glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * 1),
					ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * 1),
					1.0f)
			);
		}
		else
		{
			robot->robotModel->transform.SetPosition(
				glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * i),
					ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * randomY),
					1.0f)
			);
		}

		
		robot->robotModel->transform.SetScale(glm::vec3(ROBOT_SCALE));

		robot->robotModel->modelId = std::string("Robot " + std::to_string(i));

		robot->SetMaze(maze);

		entityManager->AddEntity("Robot " + std::to_string(i), robot);

		listOfRobots.push_back(robot);

		robot = nullptr;
	}

	delete robot;
}

void RobotsManager::PIMPL::AssignNewFriends()
{
	//shuffledListOfRobots = listOfRobots;
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::shuffle(shuffledListOfRobots.begin(), shuffledListOfRobots.end(), gen);
	std::shuffle(listOfRobots.begin(), listOfRobots.end(), gen);

	for (int i = 0; i < NUM_OF_ROBOTS; i+=2)
	{
		int friendValue = GetRandomIntNumber(5, 10);

		listOfRobots[i]->SetBestFriend(listOfRobots[i + 1], friendValue);
		listOfRobots[i]->MoveTowardsFriend();

		listOfRobots[i + 1]->SetBestFriend(listOfRobots[i], friendValue);
		listOfRobots[i + 1]->MoveTowardsFriend();
	}
}
