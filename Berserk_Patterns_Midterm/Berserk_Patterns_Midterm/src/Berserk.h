#pragma once

#include <Graphics/ApplicationWindow.h>
#include "EntityManager/EntityManager.h"
#include "Robot/RobotsManager.h"

//Derived class from the Class that helps us draw a glfw window and render our graphics in it

class Berserk : public ApplicationWindow
{

public:

	//A manager to hold various entities which creates entry points for each entity like
	//Start | Update | Adding to renderer | Adding to physics
	EntityManager entityManager;

	//Creates an instance of physics engine which calculates collision logic with all the physical objects added to it
	PhysicsEngine physicsEngine;

	//Instance of a robotmanager that handles the states of the game
	//What the robot does for every state
	// It has the major game logic
	RobotsManager* robotManager = nullptr;

	// Inherited via ApplicationWindow
	void SetUp() override;
	void PreRender() override;
	void PostRender() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;
};

