#include "Berserk.h"
#include "Maze/Maze.h"

//Is called once to setup stuff before our render loop
void Berserk::SetUp()
{
	//Physics settings
	//The callback interval of physics update
	physicsEngine.fixedStepTime = 0.01f;

	//World gravity
	physicsEngine.gravity.y = -(0.01f);

#pragma region Camera
	
	//Initializing a camera with values
	//Projection mode, width, height, near plane, far plane, fov
	camera.InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 300.0f, 45.0f);

	//Setting a camera position value
	cameraPos = glm::vec3(50.0f, 30.0f, 100.0f);

#pragma endregion

#pragma region Light

	//Loading a visual model for the light which holds tranform values 
	Model* lightModel = new Model("Assets/Models/DefaultSphere.fbx");
	Light* light = new Light();
	light->intensity = 2.5f;

	//Initializing the necessary values for light and linking the model and light transform as one
	light->InitializeLight(lightModel, Directional);

	//Adding light to the lightmanager
	//Adding multiple lights to this will calculate output based on all their values
	lightManager.AddLight(light);

	//Adding the shader the lights uniform should apply to
	lightManager.AddShader(defShader);

#pragma endregion


#pragma region Entities

	//Creating a maze entity
	Maze* maze = new Maze();

	//Creating an instance for the robotsmanager
	robotManager = new RobotsManager();

	//Passing the reference of the maze and entitymanager to the robotmanager
	robotManager->SetMaze(maze);
	robotManager->AssignEntityManager(entityManager);

	//Loading all the robots in their positions
	robotManager->LoadRobots();

	//Adding maze entity to the list of entitites of entity manager
	entityManager.AddEntity("Maze", (Entity*)maze);


#pragma endregion

#pragma region EntityManagerInit

	//Loops through all the entities and acts as a entry point to provide them renderer, shader and physics engine
	entityManager.AddToRendererAndPhysics(renderer, &defShader, physicsEngine);
	entityManager.Start();

#pragma endregion

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
