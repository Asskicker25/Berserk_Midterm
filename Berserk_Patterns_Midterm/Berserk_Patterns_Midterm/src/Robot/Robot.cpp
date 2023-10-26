#include "Robot.h"
#include "../Maze/Maze.h"

Robot::Robot()
{
	robotModel = new Model();
	robotPhyObj = new PhysicsObject();
	friendRobot = nullptr;
	destinationRobot = nullptr;
	currentFriendValue = 0;
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

void Robot::SetMaze(Maze* maze)
{
	this->maze = maze;
}

void Robot::MoveTowardsRobot(Robot* robot)
{
	destinationRobot = robot;
}

void Robot::MoveTowardsFriend()
{
	MoveTowardsRobot(friendRobot);
}

bool Robot::IsDestinationReached()
{
	if (destinationRobot == nullptr) return false;

	glm::vec3 diff = destinationRobot->robotModel->transform.position - robotModel->transform.position;

	float sqDistance = glm::dot(diff, diff);

	if (sqDistance <= (closeMinDistance * closeMinDistance))
	{
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

void Robot::ChangeColor(glm::vec3 color)
{
	if (currentColor == color) return;

	currentColor = color;
	
	for (int i = 0; i < robotModel->meshes.size(); i++)
	{
		for (int j = 0; j < robotModel->meshes[i]->vertices.size(); j++)
		{
			robotModel->meshes[i]->vertices[j].color = glm::vec4(color,1.0f);
			robotModel->meshes[i]->UpdateVertices();
		}
		//robotModel->meshes[i]->material->SetBaseColor(color);
	}
}

const int& Robot::GetFriendValue()
{
	return currentFriendValue;
}

void Robot::Start()
{
}

void Robot::Update()
{
	if (IsDestinationReached())
	{
		ChangeColor(glm::vec3(0.0f, 0.0f, 1.0f));
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
	robotPhyObj->Initialize(robotModel, AABB, DYNAMIC, SOLID);

	robotPhyObj->velocity.y = 0.0f;

	physicsEngine.AddPhysicsObject(robotPhyObj);

	renderer.AddModel(robotModel, shader);

	//ChangeColor(glm::vec3(0.0f, 0.0f, 1.0f));

	renderer;
}
