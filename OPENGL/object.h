#pragma once
#include "model.h"

class Object {



public:
	std::string name;

	glm::vec3 Pos{ 0.0f,0.0f,0.0f };
	glm::vec3 Size{ 0.0f,0.0f,0.0f };
	glm::mat4 Dir{ glm::mat4(1.0f) };

	virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) {
	}
};

