#include "Robot.h"
#include "../Maze/Maze.h"
#include "../Utilities/Random.h"

Robot::Robot()
{

	robotModel = new Model();
	robotPhyObj = new PhysicsObject();

	maze = nullptr;
	friendRobot = nullptr;
	destinationRobot = nullptr;
	currentFriendValue = 0;
	gameShape = new GameShapeIndicator();

	currentGame = None;
}

void Robot::SetBestFriend(Robot* robot, int& friendValue)
{
	this->friendRobot = robot;

	currentFriendValue = friendValue;

	Debugger::Print(robotModel->modelId, currentFriendValue);
}

Robot* Robot::GetBestFriend()
{
	return friendRobot;
}

Robot* Robot::GetDestinationRobot()
{
	return destinationRobot;
}

const int& Robot::GetFriendValue()
{
	return currentFriendValue;
}

void Robot::SetMaze(Maze* maze)
{
	this->maze = maze;
}

void Robot::Start()
{

}

void Robot::Update(float deltaTime)
{
	//Checks if the this robot and destination robot are close by the default close distance
	//RayCasts in the direction of the destination robot to check if any wall is between
	// They are not physically near if a wall is present
	if (IsDestinationReached())
	{
		isReachedDestination = true;
	}

	//Gets current path points needed after a certain interval
	//Since all the robots are always moving
	//Updates their velocity only if you have reached your destination
	if (!isReachedDestination)
	{
		if (!isAlone)
		{
			timeStep += deltaTime;
			if (timeStep > timerInterval)
			{
				GetPathPoints(pathPoints);
				timeStep = 0;
			}
		}
		UpdateVelocity(deltaTime);
	}
	else
	{
		robotPhyObj->velocity = glm::vec3(0.0f);
		timeStep = 0;
	}

	UpdateIndicatorPosition();
}

//Updates the position of the current game indicator on top of the robot head
void Robot::UpdateIndicatorPosition()
{
	switch (currentGame)
	{
	case RobotGame::None:
		break;
	case RobotGame::Euchre:
		gameShape->eucherGameModel->transform.SetPosition(
			robotModel->transform.position + indicatorOffset
		);
		break;
	case RobotGame::ExplodingKittens:
		gameShape->explodingKittensGameModel->transform.SetPosition(
			robotModel->transform.position + indicatorOffset
		);
		break;
	}
}

//Calculates current start and end point and gets the path points
void Robot::GetPathPoints(std::vector<glm::vec2>& pathPoints)
{
	currentPathIndex = 0;

	glm::vec2 startPoint = glm::vec2(robotModel->transform.position.x, robotModel->transform.position.y);
	glm::vec2 endPoint = glm::vec2(destinationRobot->robotModel->transform.position.x, destinationRobot->robotModel->transform.position.y);

	startPoint = glm::round(startPoint);
	endPoint = glm::round(endPoint);

	if (maze->GetPathPoints(startPoint, endPoint, pathPoints))
	{
	}
}

//Called to update the destination of the robot and start moving towards it
void Robot::MoveTowardsRobot(Robot* robot)
{
	destinationRobot = robot;
	isReachedDestination = false;
	isAlone = false;
	GetPathPoints(pathPoints);
}

//Called to update the destination robot to friend and move towards it
void Robot::MoveTowardsFriend()
{
	MoveTowardsRobot(friendRobot);
}

//Checks if the this robot and destination robot are close by the default close distance
//RayCasts in the direction of the destination robot to check if any wall is between
// They are not physically near if a wall is present
bool Robot::IsDestinationReached()
{
	if (destinationRobot == nullptr || isReachedDestination)
	{
		return false;
	}

	glm::vec3 diff = glm::vec3(1.0f);
	float distanceToCheck;


	if (isAlone)
	{
		diff = glm::vec3(pathPoints[pathPoints.size() - 1].x, pathPoints[pathPoints.size() - 1].y, 1.0f)
			- robotModel->transform.position;

		distanceToCheck = 1.0f;
	}
	else
	{
		diff = destinationRobot->robotModel->transform.position - robotModel->transform.position;
		distanceToCheck = closeMinDistance;

	}

	float sqDistance = glm::dot(diff, diff);




	if (sqDistance <= (distanceToCheck * distanceToCheck))
	{
		if (isAlone)
		{
			return true;
		}

		glm::vec3 collPt;
		glm::vec3 collNr;

		if (maze->RayCastMazeWall(robotModel->transform.position, diff, closeMinDistance))
		{
			return false;
		}

		if (RayCast(robotModel->transform.position, diff, destinationRobot->robotPhyObj, closeMinDistance,
			collPt, collNr))
		{
			return true;
		}
		//Debugger::Print
	}

	return false;
}

//Called to change the color of the robot
void Robot::ChangeColor(glm::vec3 color)
{
	if (currentColor == color) return;

	currentColor = color;

	for (int i = 0; i < robotModel->meshes.size(); i++)
	{
		for (int j = 0; j < robotModel->meshes[i]->vertices.size(); j++)
		{
			robotModel->meshes[i]->vertices[j].color = glm::vec4(color, 1.0f);
			robotModel->meshes[i]->UpdateVertices();
		}
		//robotModel->meshes[i]->material->SetBaseColor(color);
	}
}

//Called in the update loop, which updates the movement(velocity) of the robot based on the direction to move
void Robot::UpdateVelocity(float deltaTime)
{
	if (currentPathIndex >= pathPoints.size())
	{
		robotPhyObj->velocity = glm::vec3(0.0f);
		return;
	}

	glm::vec2 pathPoint = glm::vec2(pathPoints[currentPathIndex].x, pathPoints[currentPathIndex].y);
	//glm::vec2 pathPoint = pathPoints[currentPathIndex];

	glm::vec2 diff = pathPoint - glm::vec2(robotModel->transform.position.x, robotModel->transform.position.y);

	float sqDistance = glm::dot(diff, diff);

	if (sqDistance <= (positionReachedThreshold * positionReachedThreshold))
	{
		currentPathIndex += 1;
	}
	else
	{
		robotPhyObj->velocity = glm::vec3(glm::normalize(diff), 0.0f) * speed;
	}
}

//Assinging the current game of robot
void Robot::SetCurrentGame(RobotGame game)
{
	currentGame = game;

	switch (currentGame)
	{
	case Euchre:
		gameShape->eucherGameModel->isActive = true;
		break;
	case ExplodingKittens:
		gameShape->explodingKittensGameModel->isActive = true;
		break;
	}
}

void Robot::RemoveFromRenderer(Renderer& renderer)
{
}

void Robot::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}

void Robot::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
	Debugger::Print("Robot loaded");
	robotModel->LoadModel("Assets/Models/Robot_Eye_CentrePivot.ply");
	robotPhyObj->Initialize(robotModel, AABB, DYNAMIC, TRIGGER);

	robotPhyObj->velocity.y = 0.0f;

	physicsEngine.AddPhysicsObject(robotPhyObj);

	renderer.AddModel(robotModel, shader);

	//ChangeColor(glm::vec3(0.0f, 0.0f, 1.0f));
}

//Called to move the robot to the starting position
void Robot::MoveTowardsStartingPos()
{
	isReachedDestination = false;
	isAlone = true;

	currentPathIndex = 0;

	glm::vec2 startPoint = glm::vec2(robotModel->transform.position.x, robotModel->transform.position.y);
	glm::vec2 endPoint = glm::vec2(robotInitSpawnPos.x, robotInitSpawnPos.y);

	startPoint = glm::round(startPoint);
	endPoint = glm::round(endPoint);

	maze->GetPathPoints(startPoint, endPoint, pathPoints);
}

//Takes a random friendship value and updates the best friend if it is greater
void Robot::UpdateRobotGiftReceived(Robot* receivedFrom)
{
	int friendValue = GetRandomIntNumber(5, 10);

	if (friendValue > currentFriendValue)
	{
		this->friendRobot = receivedFrom;
	}
}
