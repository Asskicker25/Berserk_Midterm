#include "RobotsManager.h"
#include "AbstractFactory/RobotFactory.h"
#include "../Utilities/Random.h"
#include "../Maze/Maze.h"

//Game States for each question
enum RobotsManager::RobotsState
{
	FINDING_NEW_FRIENDS,
	PLAY_GAME,
	GIVE_GIFTS,
	ALONE
};

class RobotsManager::PIMPL
{
public:
	//Details required to spawn robots with unit scaling
	static const int NUM_OF_ROBOTS = 10;
	static const int ORIGIN_OFFSET = 5;
	static constexpr float ROBOT_SCALE = 0.025f;

	float timeStep = 0;
	float intervalBetweenStates = 2.0f;

	Maze* maze; 
	RobotsState robotsState = FINDING_NEW_FRIENDS;

	//List of the robots that are spawned 
	std::vector<Robot*> listOfRobots;

	//(RED) Default Color : The default color of the robot 
	//(BLUE) New Friend Reached : The color that is applied when the robots meet their friend robots 
	//(CYAN) Reached Game Arena : The color that is applied when robots find the robot that matches their game type
	//(Yello) Gift State Color : The color of the robot when it is travelling to give a gift to a robot which is not its friend
	//(White) After Gift Color : The color of the robot after it gives the gift and is moving towards its best friend
	//(Black) Alone Color : The color of the robot when it is trying to go its starting pos and be alone
	glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 newFriendReached = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 reachedGameArea = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 giftStateColor = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 afterGiftStateColor = glm::vec3(1.0f, 1.f, 1.0f);
	glm::vec3 aloneColor = glm::vec3(0.0f, 0.0f, 0.0f);

	//Instance of the factory to create robots
	RobotFactory robotFactory;
	EntityManager* entityManager;

	void LoadRobots();
	void SetRobotsState(RobotsState robotsState);

	void AssignNewFriends();
	void AssignGamesToRobot();
	void AssignGiftsForRobots();
	void AssignAloneForRobots();

	void CheckIfAllFriendsFound(float deltaTime);
	void CheckIfAllRobotsGameOver(float deltaTime);
	void CheckIfGiftGiven(float deltaTime);
	void CheckIfAllRobotsAreAlone(float deltaTime);
};


RobotsManager::RobotsManager() : pimpl { new PIMPL() }
{
}

void RobotsManager::AssignEntityManager(EntityManager& entityManager)
{
	pimpl->entityManager = &entityManager;
}

void RobotsManager::LoadRobots()
{
	pimpl->LoadRobots();
	pimpl->SetRobotsState(FINDING_NEW_FRIENDS);
}

void RobotsManager::SetMaze(Maze* maze)
{
	pimpl->maze = maze;
}

//Updated calculation that has to happen during each game state
void RobotsManager::Update(float deltaTime)
{
	switch (pimpl->robotsState)
	{
	case FINDING_NEW_FRIENDS:
		pimpl->CheckIfAllFriendsFound(deltaTime);
		break;
	case PLAY_GAME:
		pimpl->CheckIfAllRobotsGameOver(deltaTime);
		break;
	case GIVE_GIFTS:
		pimpl->CheckIfGiftGiven(deltaTime);
		break;
	case ALONE:
		pimpl->CheckIfAllRobotsAreAlone(deltaTime);
		break;
	}
}

//Creates the specified number of robots and spawns them in random positions along the Y where X is the iterated position
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

//A function used to update the current state of the game which in turn updattes the robot behaviours as mention in questions
void RobotsManager::PIMPL::SetRobotsState(RobotsState robotsState = FINDING_NEW_FRIENDS)
{
	this->robotsState = robotsState;

	switch (robotsState)
	{
	case FINDING_NEW_FRIENDS:
		AssignNewFriends();
		break;
	case PLAY_GAME:
		AssignGamesToRobot();
		break;
	case GIVE_GIFTS:
		AssignGiftsForRobots();
		break;
	case ALONE:
		AssignAloneForRobots();
		break;
	}
}

//Shuffles the list of robots 
// For random best friend logic
//Pairs the i, i+1 robots as the best friends
//Calculates a friendship value between 5 - 10
void RobotsManager::PIMPL::AssignNewFriends()
{
	//shuffledListOfRobots = listOfRobots;
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::shuffle(shuffledListOfRobots.begin(), shuffledListOfRobots.end(), gen);
	std::shuffle(listOfRobots.begin(), listOfRobots.end(), gen);

	for (int i = 0; i < NUM_OF_ROBOTS; i += 2)
	{
		int friendValue = GetRandomIntNumber(5, 10);

		listOfRobots[i]->SetBestFriend(listOfRobots[i + 1], friendValue);
		listOfRobots[i]->MoveTowardsFriend();

		listOfRobots[i + 1]->SetBestFriend(listOfRobots[i], friendValue);
		listOfRobots[i + 1]->MoveTowardsFriend();
	}
}

//Called when the state is switche dot robots playing games, Eucher and exploding kitten
//Takes the first and third robots (Non friends :- since friends are next to each other)
//Updates the rest in linear way to eucher (3 members exluding the first robot)
//5 to Exploding kitten
void RobotsManager::PIMPL::AssignGamesToRobot()
{
	listOfRobots[0]->SetCurrentGame(RobotGame::Euchre);
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

//Loop through list of robots to update the first non friend robot to the iterating robot
// Achieved by i, i+2 (since i + 1 is friend and anything other than that is non friend)
// 
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

			Debugger::Print("Robot " + std::to_string(i) + " : " + std::to_string(i - (listOfRobots.size() - 2)));
			//std::cout << " Robot " << std::to_string(i) << " : " << std::to_string(i - (listOfRobots.size() - 2)) << std::endl;
			continue;
		}

		listOfRobots[i]->MoveTowardsRobot(listOfRobots[i + 2]);
		
		Debugger::Print("Robot " + std::to_string(i) + " : " + std::to_string(i + 2));

		//std::cout << " Robot " << std::to_string(i) << " : " << std::to_string(i + 2) << std::endl;

		continue;
	}
}

//Called to make the robots go to their starting pos and be alone
void RobotsManager::PIMPL::AssignAloneForRobots()
{

	for (int i = 0; i < listOfRobots.size(); i++)
	{
		listOfRobots[i]->MoveTowardsStartingPos();
		listOfRobots[i]->ChangeColor(aloneColor);
	}
	/*for (Robot* robot : listOfRobots)
	{
		robot->MoveTowardsStartingPos();
		robot->ChangeColor(aloneColor);
	}*/
}

//Checks if all the robots have moved nearby to their friends
void RobotsManager::PIMPL::CheckIfAllFriendsFound(float deltaTime)
{
	bool found = true;
	for (Robot* robot : listOfRobots)
	{
		if (!robot->isReachedDestination)
		{
			found = false;
		}
		else
		{
			robot->ChangeColor(newFriendReached);
		}
	}

	if (found)
	{
		timeStep += deltaTime;

		if (timeStep > intervalBetweenStates)
		{
			for (Robot* robot : listOfRobots)
			{
				robot->ChangeColor(defaultColor);
			}

			timeStep = 0;
			SetRobotsState(PLAY_GAME);
		}
		
	}
}

//Checks if all robots have gone to the player with their game type and finished playing
void RobotsManager::PIMPL::CheckIfAllRobotsGameOver(float deltaTime)
{
	bool found = true;

	for (Robot* robot : listOfRobots)
	{
		if (robot->isReachedDestination)
		{
			robot->ChangeColor(reachedGameArea);
		}
	}

	for (int i = 2; i < listOfRobots.size(); i++)
	{
		if (!listOfRobots[i]->isReachedDestination)
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

//Checks if each robot has given gift to the assigned non friend robot
//Once given it moves the robot to whichever is the current best friend
//A robot's friendsip value is calculated when it is receiving a gift from other
//If friendship value is greater than current, the robot updates his best friend to the once it received the gift from
void RobotsManager::PIMPL::CheckIfGiftGiven(float deltaTime)
{
	bool found = true;
	for (Robot* robot : listOfRobots)
	{
		if (robot->isReachedDestination)
		{
			if (!robot->isGiftGiven)
			{
				robot->isGiftGiven = true;
				robot->GetDestinationRobot()->UpdateRobotGiftReceived(robot);
				robot->MoveTowardsFriend();
				robot->ChangeColor(afterGiftStateColor);
			}
			else
			{
				robot->ChangeColor(newFriendReached);
			}
		}
		else
		{
			if (robot->isGiftGiven)
			{
				found = false;
			}
		}
	}

	if (found)
	{
		timeStep += deltaTime;
		if (timeStep > intervalBetweenStates * 2.0f)
		{
			timeStep = 0;
			for (Robot* robot : listOfRobots)
			{
				robot->ChangeColor(aloneColor);
			}
			SetRobotsState(ALONE);
		}
	}
}

//Checks if all robots have gone to their starting position and is alone
//If alone starts to find new friends and continues the game loop
void RobotsManager::PIMPL::CheckIfAllRobotsAreAlone(float deltaTime)
{
	bool alone = true;
	for (Robot* robot : listOfRobots)
	{
		if(!robot->isReachedDestination)
		{
			alone = false;
		}
	}

	if (alone)
	{
		timeStep += deltaTime;
		if (timeStep > intervalBetweenStates * 2.0f)
		{
			timeStep = 0;
			for (Robot* robot : listOfRobots)
			{
				robot->ChangeColor(defaultColor);
			}

			SetRobotsState(FINDING_NEW_FRIENDS);
		}
	}
}











	 