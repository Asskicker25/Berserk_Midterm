#include "Berserk.h"
#include "Maze/Maze.h"
#include "Robot/RobotsManager.h"

void Berserk::SetUp()
{

#pragma region Camera
	
	cameraPos = glm::vec3(30.0f, 30.0f, 100.0f);

#pragma endregion

#pragma region Light

	Model* lightModel = new Model("Assets/Models/DefaultSphere.fbx");
	Light* light = new Light();
	light->intensity = 1.5f;
	light->InitializeLight(lightModel, Directional);

	lightManager.AddLight(light);
	lightManager.AddShader(defShader);

#pragma endregion



#pragma region Entities

	Maze* maze = new Maze();

	RobotsManager* robotManager = new RobotsManager();
	robotManager->AssignEntityManager(entityManager);
	robotManager->LoadRobots();

	entityManager.AddEntity("Maze", (Entity*)maze);


#pragma endregion

#pragma region EntityManagerInit

	entityManager.AddToRenderer(renderer, &defShader);
	entityManager.AddToPhysics(physicsEngine);
	entityManager.Start();

#pragma endregion

	renderer;
}

void Berserk::PreRender()
{
}

void Berserk::PostRender()
{
	entityManager.Update();
	physicsEngine.Update(deltaTime);
}

void Berserk::ProcessInput(GLFWwindow* window)
{
}

void Berserk::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void Berserk::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}