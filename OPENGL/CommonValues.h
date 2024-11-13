#pragma once


#include <string>
#include <vector>

#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

const int MAX_POINT_LIGHTS = 3;
const int MAX_BONE_COUNT = 120;

struct BoneInfo
{
	int id; // finalBoneMatrices의 index
	glm::mat4 offset;
};

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childcount;
	std::vector<AssimpNodeData> children;
};