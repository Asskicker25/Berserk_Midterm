#pragma once

#include "Debugger.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Model.h"

class Renderer
{
private :
	std::vector<Model*> models;
	std::vector<Shader*> shaders;

	glm::vec3 backGroundColor = glm::vec3(0.1f, 0.3f, 0.4f);

public:
	void Clear();
	void AddModel(Model* model, Shader* shader);
	void AddModel(Model& model, Shader& shader);
	void SetBackgroundColor(const glm::vec3& backGroundColor);
	void Draw();
};

