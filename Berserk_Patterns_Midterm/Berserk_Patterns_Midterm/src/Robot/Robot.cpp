#include "Robot.h"
#include "../Maze/Maze.h"

Robot::Robot()
{
	robotModel = new Model();
	robotPhyObj = new PhysicsObject();
	maze = nullptr;
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


void Robot::SetMaze(Maze* maze)
{
	this->maze = maze;
}

void Robot::MoveTowardsRobot(Robot* robot)
{
	destinationRobot = robot;
	GetPathPoints(pathPoints);
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
			robotModel->meshes[i]->vertices[j].color = glm::vec4(color, 1.0f);
			robotModel->meshes[i]->UpdateVertices();
		}
		//robotModel->meshes[i]->material->SetBaseColor(color);
	}
}

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

const int& Robot::GetFriendValue()
{
	return currentFriendValue;
}

void Robot::Start()
{
}

float t = 0;
void Robot::Update(float deltaTime)
{
	t += deltaTime;
	if (t > 1.0f)
	{
		GetPathPoints(pathPoints);
		t = 0;
	}
	UpdateVelocity(deltaTime);
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
