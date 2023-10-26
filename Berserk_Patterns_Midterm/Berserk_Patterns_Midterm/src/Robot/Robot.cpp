#include "Robot.h"

Robot::Robot()
{
	robotModel = new Model();
	robotPhyObj = new PhysicsObject();
	friendRobot = nullptr;
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

const int& Robot::GetFriendValue()
{
	return currentFriendValue;
}

void Robot::Start()
{
}

void Robot::Update()
{
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

	//robotPhyObj->velocity.y = -1.0f;

	physicsEngine.AddPhysicsObject(robotPhyObj);

	renderer.AddModel(robotModel, shader);
}
