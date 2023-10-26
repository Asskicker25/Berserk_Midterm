#pragma once

#include <Graphics/ApplicationWindow.h>
#include "EntityManager/EntityManager.h"
#include "Robot/RobotsManager.h"

class Berserk : public ApplicationWindow
{

private:

public:
	EntityManager entityManager;
	PhysicsEngine physicsEngine;

	RobotsManager* robotManager = nullptr;

	// Inherited via ApplicationWindow
	void SetUp() override;
	void PreRender() override;
	void PostRender() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;
};

