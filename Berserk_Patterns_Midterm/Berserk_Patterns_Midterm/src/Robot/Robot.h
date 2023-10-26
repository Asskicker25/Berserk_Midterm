#pragma once

#include "RobotBase.h"

class Robot : public RobotBase
{
private:

public:
	Robot();

	Model* robotModel;
	PhysicsObject* robotPhyObj;

	// Inherited via RobotBase
	void Start() override;
	void Update() override;
	void AddToRenderer(Renderer& renderer, Shader* shader) override;
	void AddToPhysics(PhysicsEngine& physicsEngine) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;
};

