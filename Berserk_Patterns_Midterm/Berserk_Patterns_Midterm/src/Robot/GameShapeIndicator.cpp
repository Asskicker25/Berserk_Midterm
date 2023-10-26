#include "GameShapeIndicator.h"

GameShapeIndicator::GameShapeIndicator()
{
	eucherGameModel = new Model();
	explodingKittensGameModel = new Model();
}

void GameShapeIndicator::Start()
{
}

void GameShapeIndicator::Update(float deltaTime)
{
}

void GameShapeIndicator::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
	eucherGameModel->LoadModel("Assets/Models/DefaultSphere.fbx");
	explodingKittensGameModel->LoadModel("Assets/Models/DefaultCube.fbx");

	eucherGameModel->meshes[0]->material->SetBaseColor(glm::vec3(1.0f, 0.0f, 0.0f));
	explodingKittensGameModel->meshes[0]->material->SetBaseColor(glm::vec3(1.0f, 1.0f, 0.0f));

	eucherGameModel->transform.SetScale(glm::vec3(0.75f));
	explodingKittensGameModel->transform.SetScale(glm::vec3(0.75f));

	eucherGameModel->isActive = false;
	explodingKittensGameModel->isActive = false;

	renderer.AddModel(eucherGameModel, shader);
	renderer.AddModel(explodingKittensGameModel, shader);
}

void GameShapeIndicator::RemoveFromRenderer(Renderer& renderer)
{

}

void GameShapeIndicator::RemoveFromPhysics(PhysicsEngine& physicsEngine)
{
}
