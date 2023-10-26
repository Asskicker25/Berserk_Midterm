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

void Maze::RemoveFromRenderer(Renderer& renderer)
{
}

void Maze::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}

void Maze::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
	mazeModel->LoadModel("Assets/Models/Berzerk_Level_Ouput.ply");

	renderer.AddModel(mazeModel, shader);
}
