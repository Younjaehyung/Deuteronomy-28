#include "LightMass.h"

void LightMass::SetLight ( glm::vec3 pos , glm::vec3 dir , glm::vec2 cutoff,
	float distance , glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specualr )
{
	std::cout << "//////////////////////////////HEY" << std::endl;

	m_lightControl = true;
	std::cout << "//////////////////////////////HEY" << std::endl;

	//lightData->directional = 0;
	std::cout << "//////////////////////////////HEY" << std::endl;

	lightView = glm::lookAt ( pos , pos + dir , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
	lightProjection = glm::perspective (
  glm::radians ( ( cutoff[ 0 ] + cutoff[ 1 ] ) * 2.0f ) , 1.0f , 1.0f , 20.0f );

	lightData->position = pos;
	lightData->direction = dir;
	lightData->cutoff = glm::vec2 (
	cosf ( glm::radians ( cutoff[ 0 ] ) ) , cosf ( glm::radians ( cutoff[ 0 ] + cutoff[ 1 ] ) ) );
	
	lightData->attenuation = GetAttenuationCoeff ( distance );
	lightData->ambient = ambient;
	lightData->diffuse = diffuse;
	lightData->specular = specualr;

	
}

void LightMass::SetSynLight ( glm::vec3 pos , glm::vec3 dir , glm::mat4 projection , glm::mat4 view )
{


	lightData->position = pos;
	lightData->direction = dir;
	lightProjection = projection;
	lightView = view;

}
