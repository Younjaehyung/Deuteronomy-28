#include "LightMass.h"

void LightMass::SetLight ( glm::vec3 pos , glm::vec3 dir , glm::vec2 cutoff ,
	float distance , glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specualr )
{
	int directional = 0;
	m_lightControl = false;

	lightData->directional = 0;

	lightView = glm::lookAt ( pos , pos + dir , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
	lightProjection = glm::perspective (
  glm::radians ( ( cutoff[ 0 ] + cutoff[ 1 ] ) * 2.0f ) , 1.0f , 1.0f , 20.0f );

	lightData->position = pos;
	lightData->direction = dir;
	lightData->cutoff = glm::vec2 (
	cosf ( glm::radians ( cutoff[ 0 ] ) ) , cosf ( glm::radians ( cutoff[ 0 ] + cutoff[ 1 ] ) ) );

	lightData->attenuation = GetAttenuationCoeff ( distance );
	lightData->ambient = {ambient.r / 256 , ambient.g / 256 , ambient.b / 256};
	lightData->diffuse = { diffuse.r / 256, diffuse.g / 256, diffuse.b / 256 };
	lightData->specular = { specualr.r / 256,specualr.g / 256,specualr.b / 256 };

	
}

void LightMass::SetSynLight ( glm::vec3 pos , glm::vec3 dir , glm::mat4 projection , glm::mat4 view )
{


	lightData->position = pos;
	lightData->direction = dir;
	lightProjection = projection;
	lightView = view;

}
