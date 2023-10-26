#pragma once

#include <unordered_map>
#include <string>
#include "Entity.h"

class EntityManager
{
private:
	std::unordered_map<std::string, Entity*> listOfEntities;
	std::unordered_map<std::string, Entity*>::iterator it;

	Renderer renderer;
	PhysicsEngine physicsEngine;

public:

	void AddEntity(const std::string& entityId, Entity* entity);
	void RemoveEntity(const std::string& entityId);
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine);

	void Start();
	void Update();
	void Destroy();
};

