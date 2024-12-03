#include "Player.h"
#include "Time.h"
#include "Sound.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "LightManager.h"
#include "input.h"
#include "MATMAP.h"

void Player::Update ( )
{
	animator->UpdateAnimation ( Time::DeltaTime ( ) );
	Status_Machine ( );
	Path_now ( );
	FlashLight->SetSynLight ( camera ->GetPos() , camera->GetCameraFront ( ) , camera->GetProjection ( ) , camera->GetView ( ) );

	Dir2 = camera->GetFront ( );
	Dir = camera->GetDir ( );
	camera->Camera_Ismoving ( movestat );
	
	if ( movestat == moving::stop ) {
		glm::vec3 cameraOffset = glm::vec3 ( 0.0f , 3.7f , -0.6f );
		glm::quat quaternion = glm::quat_cast ( camera->GetYaw ( ) );
		camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y  , Pos.z ) + quaternion *cameraOffset );
	}
	else if ( movestat == moving::sit ) {
		glm::vec3 cameraOffset = glm::vec3 ( 0.0f , 2.7f , -0.7f );
		glm::quat quaternion = glm::quat_cast ( camera->GetYaw ( ) );
		camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y , Pos.z ) + quaternion * cameraOffset );
	}
	else if ( movestat == moving::sit_walk ) {
		glm::vec3 cameraOffset = glm::vec3 ( 0.0f , 2.7f , -1.3f );
		glm::quat quaternion = glm::quat_cast ( camera->GetYaw ( ) );
		camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y , Pos.z ) + quaternion * cameraOffset );
	}
	else if ( movestat == moving::walk ) {
		glm::vec3 cameraOffset = glm::vec3 ( 0.0f , 3.5f , -0.5f );
		glm::quat quaternion = glm::quat_cast ( camera->GetYaw ( ) );
		camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y , Pos.z ) + quaternion * cameraOffset );
	}
	else if ( movestat == moving::run ) {
		glm::vec3 cameraOffset = glm::vec3 ( 0.0f , 3.8f , -1.7f );
		glm::quat quaternion = glm::quat_cast ( camera->GetYaw ( ) );
		camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y , Pos.z ) + quaternion * cameraOffset );
	}

	

	//std::cout << "Player Pos : " << Pos.y << std::endl;
	
}

void Player::Status_Machine ( )
{
	if ( movestat == moving::stop && animator->GetCurrAnimation() != idleAnim ) {
		animator->PlayAnimation ( idleAnim );
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->PauseSound ( );
	}
	if ( movestat == moving::sit && animator->GetCurrAnimation ( ) != sitAnim ) {
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->PauseSound ( );
		animator->PlayAnimation ( sitAnim );
	}
	if ( movestat == moving::sit_walk && animator->GetCurrAnimation ( ) != sitwalkAnim ) {
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->PauseSound ( );
		animator->PlayAnimation ( sitwalkAnim );
	}
	if ( movestat == moving::walk && animator->GetCurrAnimation ( ) != walkAnim ) {
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->PauseSound ( );
		animator->PlayAnimation ( walkAnim );
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->ReplaySound ( 0.7f);
	}
	if ( movestat == moving::run && animator->GetCurrAnimation ( ) != runAnim ) {
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->PauseSound ( );
		animator->PlayAnimation ( runAnim );
		SoundManager::getInstance ( ).GetSoundID ( "Walk" )->ReplaySound ( 0.7f );
		SoundManager::getInstance ( ).GetSoundID ( "HeartBeat" )->ReplaySound ( 1.3f );
	}
	

}



void Player::Render ( const Program* program, glm::mat4 _cameraTransform )
{
	
	//_shader->Use ( );
	//auto camerapos = CameraManager::getInstance ( ).GetPos ( );
	//auto view = CameraManager::getInstance ( ).GetView ( );
	//auto projection = CameraManager::getInstance ( ).GetProjection ( );

	//glm::vec3 direction = glm::normalize ( glm::vec3 ( 1.0f , 0.0f , 1.0f ) ); // 바라볼 방향
	//glm::vec3 up = glm::vec3 ( 0.0f , 1.0f , 0.0f ); // 업 벡터
	//glm::quat rotation = glm::quatLookAt ( direction , up );
	//glm::mat4 modelMatrix = glm::mat4_cast ( rotation );

	//modelTransform =
	//	glm::translate ( glm::mat4 ( 1.0f ) , Pos) *
	//	modelMatrix *
	//	glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
	//auto transform = projection * view * modelTransform;
	//_shader->SetUniform ( "modelTransform" , modelTransform );
	//_shader->SetUniform ( "transform" , transform );

	
	const auto& transforms = animator->GetFinalBoneMatrices ( );

	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3(Pos.x,Pos.y,Pos.z) )
		*camera->GetYaw()
		* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 0.0f ) , glm::vec3 (0.0 , 1.0 , 0.0 ) ) );

	program->SetUniform ( "transform" , _cameraTransform
		* glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( Pos.x , Pos.y , Pos.z  ) ) * camera->GetYaw ( )
		*glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 0.0f ) , glm::vec3 ( 0.0 , 1.0 , 0.0 ) ) );


	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );
	LightManager::getInstance ( ).GetLightSetting ( program );


	model->Draw ( program  );
}

void Player::RenderShadow ( glm::mat4 lightView , const Program* program )
{
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );

	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( Pos.x , Pos.y , Pos.z ) )
	* camera->GetYaw ( )
	* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 0.0f ) , glm::vec3 ( 0.0 , 1.0 , 0.0 ) ) );

	program->SetUniform ( "transform" , lightView
		* glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( Pos.x , Pos.y , Pos.z ) ) * camera->GetYaw ( )
		* glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 0.0f ) , glm::vec3 ( 0.0 , 1.0 , 0.0 ) ) );

	model->Draw ( program );
}



void Player::Initialize ( const std::string& strName )
{
	camera = new Camera;

	name = "player";

	UBO = UBOBUFFER::Create ( 200 );

	_model = Model::Load ( strName );
	model = _model.get ( );
	idleAnim = new Animation ( strName , model );
	walkAnim = new Animation ( "./model/SibalGLB/SibalWalk.glb" , model );
	runAnim = new Animation ( "./model/SibalGLB/SibalRun.glb" , model );
	sitwalkAnim = new Animation ( "./model/SibalGLB/SibalCrounchWalk.glb"  , model );
	sitAnim = new Animation ( "./model/SibalGLB/SibalCrounchIdle.glb"  , model );
	

	animator = new Animator ( idleAnim );
	
	FlashLight = new LightMass;

	FlashLight->SetLight( glm::vec3 ( 2.0f , 4.0f , -1.0f ) , glm::vec3 ( 3.0f , 0.0f , 0.0f ) , glm::vec2 ( 20.0f , 5.0f ) );
	
	LightManager::getInstance ( ).AddLight ( FlashLight );

	std::cerr << "Player INITIALIZE!" << std::endl;
	if ( !_model ) {
		std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
		return;


	}
	

}

void Player::Input ( GLFWwindow* window ) {
	movestat = moving::stop;
	
	glm::vec3 cameraDirectionXZ = glm::normalize ( glm::vec3 ( Dir2.x , 0.0f , Dir2.z ) );
	auto cameraRight = glm::normalize ( glm::cross ( glm::vec3(0.0f,1.0f,0.0f) , cameraDirectionXZ ) );

	float speed = 8 * Time::DeltaTime ( );


	glm::vec3 _pos = Pos;

	

	if ( (running_stamina>=0 )&&glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS ) {
		Pos += 1.5f*speed * cameraDirectionXZ;
		movestat = moving::run;
		
		//SoundManager::getInstance ( ).GetSoundID ( "charge" )->ReplaySound ( );
	}
	else if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		Pos += 0.7f * speed * cameraDirectionXZ;
		movestat = moving::sit_walk;
	}
	else if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS ) {
		Pos += speed * cameraDirectionXZ;
		movestat = moving::walk;
		//SoundManager::getInstance ( ).GetSoundID ( "charge" )->ReplaySound ( );
	}


	if ( ( running_stamina >= 0 ) && glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS ) {
		Pos -= 1.5f * speed * cameraDirectionXZ;
		movestat = moving::run;
		
	}
	else if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		Pos -= 0.7f * speed * cameraDirectionXZ;
		movestat = moving::sit_walk;
	}
	else if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS ) {
		Pos -= speed * cameraDirectionXZ;
		movestat = moving::walk;
	}



	if ( ( running_stamina >= 0 ) && glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS ) {
		Pos -= 1.5f * speed * cameraRight;
		movestat = moving::run;
		
	}
	else if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		Pos -= 0.7f * speed * cameraRight;
		movestat = moving::sit_walk;
	}
	else if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS ) {
		Pos -= speed * cameraRight;
		movestat = moving::walk;
	}
	


	if ( ( running_stamina >= 0 ) && glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS ) {
		Pos += 1.5f * speed * cameraRight;
		movestat = moving::run;
		
	}
	else if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS && glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		Pos += 0.7f * speed * cameraRight;
		movestat = moving::sit_walk;
	}
	else if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS ) {
		Pos += speed * cameraRight;
		movestat = moving::walk;
	}

	glm::ivec2 now;
	Path_now ( Pos , now);
	std::cout << "POS1" << std::endl;
	if ( now.x < 0 || now.y < 0 ) {

	}
	else if ( grid[ now.y ][now.x] != 0 && grid[ now.y ][ now.x ] != 3 ) {
		Pos = _pos;
	}
	std::cout << "POS2" << std::endl;

	if ( movestat == moving::run ) {

		running_stamina -= Time::DeltaTime ( );
		if ( running_stamina < 0 ) {
			running_stamina = -1;
		}
	}
	else {
		running_stamina += Time::DeltaTime ( )/5;
		if ( running_stamina >= 10 ) {
			running_stamina = 10;
		}
	}

	if ( (movestat == moving::stop)&&glfwGetKey ( window , GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS ) {
		
		movestat = moving::sit;
	}
	
	if ( input::GetKeyDown ( eKeyCode::F ) ) {
		FlashLight->Switch_lightControl() = !FlashLight->Switch_lightControl ( );
		FlashLight_switch = !FlashLight_switch;
	}



}

bool Player::HandleCollision ( Object* object )
{
	if ( object->objectID == eLayerType::Item ) {
		Item* newItem = new Item;
		Inventory.push_back ( newItem );

	}

	return true;

}

void Player::Path_now ( glm::vec3 Pos , glm::ivec2& path_now ) {
	//float dul = Pos.x - int ( Pos.x );

	path_now.x = ( int ( Pos.x ) - ( int ( Pos.x ) % 3 ) ) / 3;
	// Z축 인덱스 계산
	path_now.y = ( int ( Pos.z ) / 3 ) * 1; // 기본적으로 3의 배수로 변환
	if ( Pos.z > 0 && int ( Pos.z ) % 3 != 0 ) {
		path_now.y += 1; // 양수 방향 보정

	}
	path_now.y = -path_now.y;


	if ( Pos.x < 0 ) {
		path_now.x -= 1;

	}



	//std::cout << "path_now_x : " << path_now.x << std::endl;
	//std::cout << "path_now_z : " << path_now.y << std::endl;
}