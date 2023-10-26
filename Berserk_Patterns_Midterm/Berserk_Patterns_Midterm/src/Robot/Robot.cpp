#include "Robot.h"

Robot::Robot()
{
	robotModel = new Model();
	robotPhyObj = new PhysicsObject();
}

void Robot::Start()
{
}

void Robot::Update()
{
}

void Robot::AddToRenderer(Renderer& renderer, Shader* shader)
{
	Debugger::Print("Robot loaded");
	robotModel->LoadModel("Assets/Models/Robot_Eye_CentrePivot.ply");
	//robotModel->transform.SetPosition(glm::vec3(5.0f, 10.0f, 1.0f));
	//robotModel->transform.SetScale(glm::vec3(0.05f));

	renderer.AddModel(robotModel, shader);
}

void Robot::AddToPhysics(PhysicsEngine& physicsEngine)
{
}

void Robot::RemoveFromRenderer(Renderer& renderer)
{
}

void Robot::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}
