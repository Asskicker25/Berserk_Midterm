#pragma once

#include "RobotBase.h"

class Robot : public RobotBase
{
private:
	Robot* friendRobot;
	Robot* destinationRobot;

	int currentFriendValue;
	int closeMinDistance = 10.0f;

	glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f);

public:
	Robot();

	const int& GetFriendValue();
	void SetBestFriend(Robot* robot, int& friendValue);
	Robot* GetBestFriend();

	void MoveTowardsRobot(Robot* robot);
	void MoveTowardsFriend();

	bool IsDestinationReached();

	void ChangeColor(glm::vec3 color);

	// Inherited via RobotBase
	void Start() override;
	void Update() override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
};

