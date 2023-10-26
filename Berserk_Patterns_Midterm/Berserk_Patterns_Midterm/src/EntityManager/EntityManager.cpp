#include "EntityManager.h"
#include <Graphics/Renderer.h>

void EntityManager::AddEntity(const std::string& entityId, Entity* entity)
{
	listOfEntities[entityId] = entity;
}

void EntityManager::RemoveEntity(const std::string& entityId)
{
	listOfEntities.erase(entityId);
}

void EntityManager::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
	this->renderer = renderer;
	this->physicsEngine = physicsEngine;

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->AddToRendererAndPhysics(renderer, shader,physicsEngine);
	}
}

void EntityManager::Start()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Start();
	}
}

void EntityManager::Update()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Update();
	}
}

void EntityManager::Destroy()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->RemoveFromRenderer(renderer);
		it->second->RemoveFromPhysics(physicsEngine);
	}
}

