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
	Maze* maze;
	//std::vector<Robot*> shuffledListOfRobots;
	glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 newFriendReached = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 reachedGameArea = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 giftStateColor = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 afterGiftStateColor = glm::vec3(1.0f, 1.f, 1.0f);

	RobotFactory robotFactory;
	EntityManager* entityManager;

	void LoadRobots();
	void AssignNewFriends();
	void AssignGamesToRobot();
	void AssignGiftsForRobots();
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
	this->robotsState = robotsState;
	switch (robotsState)
	{
	case FINDING_NEW_FRIENDS:
		pimpl->AssignNewFriends();
		break;
	case PLAY_GAME:
		pimpl->AssignGamesToRobot();
		break;
	case GIVE_GIFTS:
		pimpl->AssignGiftsForRobots();
		break;
	case ALONE:
		break;
	}
}

void RobotsManager::Update(float deltaTime)
{
	switch (robotsState)
	{
	case FINDING_NEW_FRIENDS:
		CheckIfAllFriendsFound(deltaTime);
		break;
	case PLAY_GAME:
		CheckIfAllRobotsGameOver(deltaTime);
		break;
	case GIVE_GIFTS:
		CheckIfGiftGiven(deltaTime);
		break;
	case ALONE:
		break;
	}
}

void RobotsManager::CheckIfAllFriendsFound(float deltaTime)
{
	bool found = true;
	for (Robot* robot : pimpl->listOfRobots)
	{
		if (!robot->isReachedDestination)
		{
			found = false;
		}
		else
		{
			robot->ChangeColor(pimpl->newFriendReached);
		}
	}

	if (found)
	{
		timeStep += deltaTime;

		if (timeStep > intervalBetweenStates)
		{
			for (Robot* robot : pimpl->listOfRobots)
			{
				robot->ChangeColor(pimpl->defaultColor);
			}

			timeStep = 0;
			SetRobotsState(PLAY_GAME);
		}
		
	}
}

void RobotsManager::CheckIfAllRobotsGameOver(float deltaTime)
{
	bool found = true;

	for (Robot* robot : pimpl->listOfRobots)
	{
		if (robot->isReachedDestination)
		{
			robot->ChangeColor(pimpl->reachedGameArea);
		}
	}

	for (int i = 2; i < pimpl->listOfRobots.size(); i++)
	{
		if (!pimpl->listOfRobots[i]->isReachedDestination)
		{
			found = false;
			break;
		}
	}

	if (found)
	{
		timeStep += deltaTime;
		if (timeStep > intervalBetweenStates * 2.0f)
		{
			timeStep = 0;
			SetRobotsState(GIVE_GIFTS);
		}
	}
}

void RobotsManager::CheckIfGiftGiven(float deltaTime)
{

	for (Robot* robot : pimpl->listOfRobots)
	{
		if (robot->isReachedDestination)
		{
			if (!robot->isGiftGiven)
			{
				robot->isGiftGiven = true;
				robot->GetDestinationRobot()->UpdateRobotGiftReceived(robot);
				robot->MoveTowardsFriend();
				robot->ChangeColor(pimpl->afterGiftStateColor);
			}
		}
	}

	/*if (found)
	{
		timeStep += deltaTime;
		if (timeStep > intervalBetweenStates * 2.0f)
		{
			timeStep = 0;
			SetRobotsState(GIVE_GIFTS);
		}
	}*/
}

void RobotsManager::PIMPL::LoadRobots()
{
	Robot* robot;
	for (int i = 0; i < NUM_OF_ROBOTS; i++)
	{
		robot = (Robot*)robotFactory.CreateRobot();

		int randomX = GetRandomIntNumber(0, Maze::MAZE_X_SIZE - 1);
		int randomY = GetRandomIntNumber(0, Maze::MAZE_Y_SIZE - 1);

		/*if (i == 0)
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
				glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * 1 ),
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
		}*/

		robot->robotInitSpawnPos = glm::vec3(ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * i),
			ORIGIN_OFFSET + (Maze::MAZE_CELL_SIZE * randomY),
			1.0f);

		robot->robotModel->transform.SetPosition(robot->robotInitSpawnPos);
		
		robot->robotModel->transform.SetScale(glm::vec3(ROBOT_SCALE));

		robot->robotModel->modelId = std::string("Robot " + std::to_string(i));

		robot->SetMaze(maze);

		entityManager->AddEntity("Robot " + std::to_string(i), robot);
		entityManager->AddEntity("Indicator " + std::to_string(i), (Entity*)robot->gameShape);

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

void RobotsManager::PIMPL::AssignGamesToRobot()
{
	listOfRobots[0]->SetCurrentGame(RobotGame::Euchre) ;
	listOfRobots[2]->SetCurrentGame(RobotGame::ExplodingKittens);

	int eucherCount = 0;

	for (int i = 1; i < listOfRobots.size(); i++)
	{
		if (i == 2) continue;

		if (eucherCount < 3)
		{
			listOfRobots[i]->SetCurrentGame(RobotGame::Euchre);
			listOfRobots[i]->MoveTowardsRobot(listOfRobots[0]);
			eucherCount++;

			continue;
		}

		listOfRobots[i]->SetCurrentGame(RobotGame::ExplodingKittens);
		listOfRobots[i]->MoveTowardsRobot(listOfRobots[2]);
	}

}

//0 2 //1 3 //2 4 //3 5 //4 6 //5 7 //6 8 //7 9 //8 0 // 9 1
void RobotsManager::PIMPL::AssignGiftsForRobots()
{

	for (int i = 0; i < listOfRobots.size(); i++)
	{

		listOfRobots[i]->gameShape->eucherGameModel->isActive = false;
		listOfRobots[i]->gameShape->explodingKittensGameModel->isActive = false;

		listOfRobots[i]->ChangeColor(giftStateColor);

		if (i + 2 >= listOfRobots.size())
		{
			listOfRobots[i]->MoveTowardsRobot(listOfRobots[i - (listOfRobots.size() - 2)]);

			std::cout << " Robot " << std::to_string(i) << " : " << std::to_string(i - (listOfRobots.size() - 2)) << std::endl;
			continue;
		}

		listOfRobots[i]->MoveTowardsRobot(listOfRobots[i + 2]);
		std::cout << " Robot " << std::to_string(i) << " : " << std::to_string(i + 2) << std::endl;

		continue;
	}
}

	 