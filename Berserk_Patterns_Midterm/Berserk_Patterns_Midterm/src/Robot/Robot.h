#pragma once

#include "RobotBase.h"

class Robot : public RobotBase
{
private:
	Robot* friendRobot;

	int currentFriendValue;

public:
	Robot();

	void SetBestFriend(Robot* robot, int& friendValue);
	Robot* GetBestFriend();

	const int& GetFriendValue();

	// Inherited via RobotBase
	void Start() override;
	void Update() override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

