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

#pragma region Colliders
	//Bottom Border
	Model* cube1 = new Model("Assets/Models/CubeWithLeftPivot.fbx");
	cube1->transform.SetPosition(glm::vec3(0.0f - 0.5f, 0.0f - 0.5f, 1.0f));
	cube1->transform.SetScale(glm::vec3(100.0f, 1.0f, 1.0f));

	PhysicsObject* cubePhy1 = new PhysicsObject();
	cubePhy1->Initialize(cube1, AABB, STATIC, SOLID);
	physicsEngine.AddPhysicsObject(cubePhy1);
	//Top Border
	/*Model* cube2 = new Model();
	cube2 = &(*cube1);
	cube2->transform.SetPosition(glm::vec3(0.0f, 60.0f, 1.0f));*/


	renderer.AddModel(cube1, shader);
#pragma endregion

	

}
