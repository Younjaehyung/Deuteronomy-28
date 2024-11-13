#include "character.h"
#include "Time.h"


void character::Update ( )
{
}

void character::Render ( const Program* program )
{

	animator->UpdateAnimation ( Time::DeltaTime ( ) );
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	//
	//for ( int i = 0; i < transforms.size ( ); i++ )
	//{
	//	UBO->UpdateBoneMatrices ( transforms );
	//	char locbuff[ 100 ] = { '\0' };
	//	snprintf ( locbuff , sizeof ( locbuff ) , "finalBonesMatrices[%d]" , i );
	//	program->SetUniform ( "finalBonesMatrices[" + std::to_string ( i ) + "]" , transforms[ i ] );

	//}

	program->SetUniform ( "modelMat" , ( glm::mat4 ( 1.0f ) ) );
	program->SetUniform ( "PVM" , CameraManager::getInstance ( ).Camera_transform ( )* glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0) ));
	program->SetUniform ( "normalMat" , ( glm::mat3 ( 1.0f ) ) );

	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );

	model->Draw ( program );
}


void character::Initialize ( const std::string& strName )
{

	UBO = UBOBUFFER::Create (200 );

	_model = Model::Load ( strName );
	model = _model.get ( );
	Animation* idleAnim = new Animation ( strName , model );
	animator = new Animator ( idleAnim );

	std::cerr << "OBJECT INITIALIZE!" << std::endl;
	if ( !_model ) {
		std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
		return;


	}


}