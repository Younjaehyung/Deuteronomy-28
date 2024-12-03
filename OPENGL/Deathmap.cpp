#include "Deathmap.h"
#include "LightManager.h"

void Deathmap::Update ( )
{



}

void Deathmap::Render ( const Program* program , glm::mat4 _cameraTransform )
{
	LightManager::getInstance ( ).GetLightSetting ( program );
	m_model->Draw ( program );

}

void Deathmap::Initialize ( const std::string& strName )
{
	m_model = Model::Load ( strName );
	if ( !m_model ) {
		std::cerr << "program UserSetError id : " << m_model->Get ( ) << std::endl;
		return;
	}
}

void Deathmap::RenderShadow ( glm::mat4 lightView , const Program* program )
{
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
	program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) );
	//std::cout << "model" << std::endl;
	m_model->Draw ( program );
}
