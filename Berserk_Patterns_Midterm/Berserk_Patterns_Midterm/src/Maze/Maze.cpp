#include "Maze.h"

Maze::Maze()
{
	mazeModel = new Model();
}

bool Maze::RayCastMazeWall(glm::vec3& origin, glm::vec3& direction, float rayDist)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (i == 17)
		{

		}
		glm::vec3 collPt, collNr;
		if (RayCast(origin, direction, colliders[i], rayDist, collPt, collNr))
		{
			return true;
		}
	}
	return false;
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

	float centerOffset = 0.5f;
	colliders.clear();
	collidersData.clear();

	//Horizontal
	collidersData.push_back({ 0,0,100,1});
	collidersData.push_back({ 0,6,100,1});
	collidersData.push_back({ 1,1,11,1});
	collidersData.push_back({ 6,1,11,1});
	collidersData.push_back({ 6,1,11,1});
	collidersData.push_back({ 3,2,11,1});
	collidersData.push_back({ 3,3,11,1});
	collidersData.push_back({ 7,2,11,1});
	collidersData.push_back({ 1,3,11,1});
	collidersData.push_back({ 5,3,11,1});
	collidersData.push_back({ 8,3,11,1});
	collidersData.push_back({ 1,4,21,1});
	collidersData.push_back({ 4,4,11,1});
	collidersData.push_back({ 6,4,11,1});
	collidersData.push_back({ 0,5,41,1});
	collidersData.push_back({ 7,5,11,1});
	collidersData.push_back({ 9,5,11,1});

	//Vertical
	collidersData.push_back({ 0,0,1,61 });
	collidersData.push_back({ 10,0,1,61 });
	collidersData.push_back({ 1,1,1,21 });
	collidersData.push_back({ 4,0,1,11 });
	collidersData.push_back({ 8,0,1,21 });
	collidersData.push_back({ 3,1,1,11 });
	collidersData.push_back({ 5,1,1,21 });
	collidersData.push_back({ 6,1,1,11 });
	collidersData.push_back({ 7,1,1,21 });
	collidersData.push_back({ 9,1,1,21 });
	collidersData.push_back({ 2,2,1,11 });
	collidersData.push_back({ 4,3,1,11 });
	collidersData.push_back({ 8,3,1,11 });
	collidersData.push_back({ 9,3,1,11 });
	collidersData.push_back({ 6,4,1,11 });
	collidersData.push_back({ 7,4,1,11 });
	collidersData.push_back({ 5,5,1,11 });

	for (int i = 0; i < collidersData.size(); i++)
	{
		Model* cube = new Model("Assets/Models/CubeWithLeftPivot.fbx");
		cube->transform.SetPosition(
			glm::vec3((10.0f * collidersData[i].xPos) - centerOffset, (collidersData[i].yPos * 10.0f) - centerOffset, 1.0f));
		cube->transform.SetScale(glm::vec3(collidersData[i].xScale, collidersData[i].yScale, 1.0f));

		PhysicsObject* cubePhy = new PhysicsObject();
		cubePhy->Initialize(cube, AABB, STATIC, SOLID);
		physicsEngine.AddPhysicsObject(cubePhy);
		colliders.push_back(cubePhy);

		//renderer.AddModel(cube, shader);
	}

#pragma endregion

	

}
