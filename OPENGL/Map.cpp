#include "Map.h"
#include "Time.h"


void Map::Update ( )
{
}

void Map::Render ( const Program* program )
{

	animator->UpdateAnimation ( Time::DeltaTime ( ) );
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	for ( int i = 0; i < transforms.size ( ); i++ )
	{
	
		char locbuff[ 100 ] = { '\0' };
		snprintf ( locbuff , sizeof ( locbuff ) , "finalBonesMatrices[%d]" , i );

		int loc = glGetUniformLocation ( program->Get ( ) , locbuff );
		glUniformMatrix4fv ( loc , 1 , false , glm::value_ptr ( transforms[ i ] ) );
	}
		program->SetUniform ( "modelMat" , glm::mat4(1.0f) );
		program->SetUniform ( "PVM" , CameraManager::getInstance ( ).Camera_transform ( ) );
		program->SetUniform ( "normalMat" ,  ( glm::mat4 ( 1.0f ) ) );
	
	//glm::mat3 ( glm::transpose ( glm::inverse
		model->Draw ( program );
}


void Map::Initialize ( const std::string& strName )
{
	
	
	std::string strName2 = "./model/man.fbx";
	_model = Model::Load ( strName2 );
	model = _model.get ( );
    Animation* idleAnim = new Animation ( strName , model );
	std::cerr << "CCC" << std::endl;
    animator = new Animator ( idleAnim );
    if ( !_model ) {
        std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
        return;


    }

	
}
