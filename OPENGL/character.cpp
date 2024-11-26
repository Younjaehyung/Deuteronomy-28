#include "character.h"
#include "Time.h"
#include  "LightManager.h"

void character::Update ( )
{
	//Algorithm ( );
	/*Dir2 = camera->GetFront ( );
	Dir = camera->GetDir ( );*/
	//camera->Camera_Ismoving ( movestat );
	//카메라 흔들림 주석형

}

void character::Render_2pass ( const Program* program )
{
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	program->SetUniform ( "transform" , CameraManager::getInstance ( ).Camera_transform ( ) * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );

	LightManager::getInstance ( ).GetLightSetting ( program );
	model->Draw ( program );
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


	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );
	

	model->Draw ( program );
}


void character::Initialize ( const std::string& strName )
{
	name = "monster";

	UBO = UBOBUFFER::Create (200 );

	_model = Model::Load ( strName );
	model = _model.get ( );
	Animation* idleAnim = new Animation ( strName , model );
	animator = new Animator ( idleAnim );
	CollisionManager::getInstance ( ).SetCollision ( this );

	std::cerr << "OBJECT INITIALIZE!" << std::endl;
	if ( !_model ) {
		std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
		return;


	}


}

void character::RenderShadow ( glm::mat4 lightView , const Program* program )
{
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );

	Render ( program );
}

void character::Algorithm ( )
{
	Path_now ( );
	
	if ( algorithm->RenewTime ( ) ) {
		algorithm->A_star ( );
		pathindex = 0;
	}

	int goalx=0;
	int goaly=0;
	
	int Lastgoalx = 0;
	int Lastgoaly = 0;

	if ( algorithm->path.size() > 0 ) {
		std::tuple<int , int> gotoPath = algorithm->path[ pathindex ];
		std::tie ( goalx , goaly ) = gotoPath;
	}
	else {
		std::cout << "NOT PATH IS RENEW" << std::endl;
		return;
	}
	std::tuple<int , int> gotoPath2 = algorithm->path[ algorithm->path.size ( ) - 1 ];
	std::tie ( Lastgoalx , Lastgoaly ) = gotoPath2;
	if ( path_now_x == Lastgoalx && path_now_z == Lastgoaly ) {
		return;
	}


	if ( path_now_x == goalx && path_now_z == goaly ) {
		if(algorithm->path.size ( ) -1> pathindex ){
			pathindex += 1;
		}
		else{
			std::cout << "GOAL IN" << std::endl;
			return;
		}

	}
	else {
		float speed = 10.0f * Time::DeltaTime ( );
		glm::mat4 dir_temp = glm::mat4 ( 1.0f );
		glm::vec3 eulerAngles ( glm::radians ( 0.0f ) , glm::radians ( 0.0f ) , glm::radians ( 0.0f ) ); // XYZ 회전
		
		if ( path_now_x < goalx ) {

			Pos.x += speed;
			eulerAngles.y = glm::radians ( -90.0f );
			//dir=glm::rotate()
		}
		else if ( path_now_x > goalx ) {
			Pos.x -= speed;
			eulerAngles.y = glm::radians ( 90.0f );
		}
		
		if ( path_now_z < goaly ) {
			Pos.z -= speed;
			eulerAngles.y = glm::radians ( 0.0f );
		}
		else if ( path_now_z > goaly ) {
			Pos.z += speed;
			eulerAngles.y = glm::radians ( 180.0f );
		}
		
		quaternion = glm::quat ( eulerAngles );
		
	}
	
	

}



