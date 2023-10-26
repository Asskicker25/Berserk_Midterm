#include "Maze.h"

Maze::Maze()
{
	mazeModel = new Model();
}

void Maze::Start()
{
}

void Maze::Update()
{
}

void Maze::AddToRenderer(Renderer& renderer, Shader* shader)
{
	mazeModel->LoadModel("Assets/Models/Berzerk_Level_Ouput.ply");
	
	renderer.AddModel(mazeModel, shader);
}

void Maze::AddToPhysics(PhysicsEngine& physicsEngine)
{
}

void Maze::RemoveFromRenderer(Renderer& renderer)
{
}

void Maze::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}
