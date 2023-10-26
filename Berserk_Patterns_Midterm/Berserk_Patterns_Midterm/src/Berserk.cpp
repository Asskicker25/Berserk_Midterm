#include "Berserk.h"
#include "Maze/Maze.h"

void Berserk::SetUp()
{

	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = -(0.01f);

#pragma region Camera
	
	camera.InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 300.0f, 45.0f);
	cameraPos = glm::vec3(50.0f, 30.0f, 100.0f);

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

	robotManager = new RobotsManager();
	robotManager->SetMaze(maze);
	robotManager->AssignEntityManager(entityManager);
	robotManager->LoadRobots();

	entityManager.AddEntity("Maze", (Entity*)maze);


#pragma endregion

#pragma region EntityManagerInit

	entityManager.AddToRendererAndPhysics(renderer, &defShader, physicsEngine);
	entityManager.Start();

#pragma endregion

	renderer;
}

void Berserk::PreRender()
{
}

void Berserk::PostRender()
{
	entityManager.Update(deltaTime);
	physicsEngine.Update(deltaTime);
	robotManager->Update(deltaTime);
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
