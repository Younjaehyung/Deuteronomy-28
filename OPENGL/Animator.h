#pragma once
#include <vector>

#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "CommonValues.h"


class Animation;

class Animator
{
public:
	Animator ( Animation* animation );

	void UpdateAnimation ( float deltaTime );
	void PlayAnimation ( Animation* pAnimation );
	void CalculateBoneTransform ( const AssimpNodeData* node , glm::mat4 parentTransform );
	Animation* GetCurrAnimation ( ) { return currentAnimation; }
	std::vector<glm::mat4> GetFinalBoneMatrices ( );

private:
	std::vector<glm::mat4> finalBoneMatrices;
	Animation* currentAnimation;
	float currentTime;
	float deltaTime;
};

