#include "character.h"
#include "Time.h"
#include  "LightManager.h"
#include "Sound.h"

const float distance1 = 81.0f;
const float distance2 = 196.0f;
const glm::vec3 cameraOffset(0.0f,0.0f,-1.0f);

void character::Update ( )
{
	animator->UpdateAnimation ( Time::DeltaTime ( ) );
	//Algorithm ( );
	Status_Machine ( );
	SetEyeLight ( );
	
	/*Dir2 = camera->GetFront ( );
	Dir = camera->GetDir ( );*/
	//camera->Camera_Ismoving ( movestat );
	//카메라 흔들림 주석형

}

void character::SetEyeLight ( ) {
	
	camera->Camera_set ( glm::vec3 ( Pos.x , Pos.y + 6.4 , Pos.z ) + quaternion * cameraOffset );
	camera->Update ( );
	camera->GetView ( ) = glm::lookAt ( camera->GetPos() , camera->GetPos ( ) + quaternion*glm::vec3(0.0f,0.0f,-1.0f) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
	
	
	EYELIGHT->SetSynLight ( camera->GetPos() , quaternion * glm::vec3 ( 0.0f , 0.0f , -1.0f ) , camera->GetProjection ( ) , camera->GetView ( ) );
}

bool character::HandleCollision ( Object* object )
{

	if ( object->objectID == eLayerType::Player ) {
		
	}


	return false;
}

void character::Render_2pass ( const Program* program , glm::mat4 _cameraTransform )
{
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	program->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );

	LightManager::getInstance ( ).GetLightSetting ( program );
	model->Draw ( program );
}
void character::RenderShadow ( glm::mat4 lightView , const Program* program )
{
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	program->SetUniform ( "transform" , lightView * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );

	model->Draw ( program );
}

void character::Render ( const Program* program , glm::mat4 _cameraTransform )
{

	
	const auto& transforms = animator->GetFinalBoneMatrices ( );
	program->SetUniform ( "modelTransform" , glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	program->SetUniform ( "transform" , _cameraTransform * glm::translate ( glm::mat4 ( 1.0f ) , Pos ) * glm::mat4_cast ( quaternion ) );
	UBO->Bind ( program->Get ( ) , "Bones" );
	UBO->UpdateBoneMatrices ( transforms );

	LightManager::getInstance ( ).GetLightSetting ( program );
	model->Draw ( program );
}


void character::Initialize ( const std::string& strName )
{

	camera = new Camera;
	name = "monster";
	_model = Model::Load ( strName );
	model = _model.get ( );
	idleAnim = new Animation ( "./model/HULK1/HulkIdle.glb" , model );
	attackAnim = new Animation ( "./model/HULK1/HulkAttack.glb" , model );
	runAnim = new Animation ( "./model/HULK1/HulkRun.glb" , model );
	walkAnim = new Animation ( "./model/HULK1/HulkWalk.glb" , model );
	sceramAnim = new Animation ( "./model/HULK1/HulkScream.glb" , model );

	UBO = UBOBUFFER::Create (200 );

	EYELIGHT = new LightMass;

	EYELIGHT->SetLight ( glm::vec3 ( 2.0f , 4.0f , -1.0f ) , glm::vec3 ( 3.0f , 0.0f , 0.0f ) , glm::vec2 ( 15.0f , 13.0f ),140.0f,glm::vec3(0.0f), glm::vec3 ( 255.0f , 25.0f,0.0f ), glm::vec3 ( 255.0f,25.0f,0.0f ) );

	LightManager::getInstance ( ).AddLight ( EYELIGHT );

	Animation* idleAnim = new Animation ( strName , model );
	animator = new Animator ( idleAnim );
	//Pos = glm::vec3 (5.0f,0.0f,-1.0f );
	std::cerr << "OBJECT INITIALIZE!" << std::endl;
	if ( !_model ) {
		std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
		return;


	}


}



bool character::DynamicAlgorithm ( )
{
	Path_now ( );

	if ( algorithm->RenewTime ( ) ) {
		algorithm->A_star ( );
		pathindex = 0;
	}

	int goalx = 0;
	int goaly = 0;

	int Lastgoalx = 0;
	int Lastgoaly = 0;

	if ( algorithm->path.size ( ) > 0 ) {
		std::tuple<int , int> gotoPath = algorithm->path[ pathindex ];
		std::tie ( goalx , goaly ) = gotoPath;
	}
	else {
		std::cout << "NOT PATH IS RENEW" << std::endl;
		return false;
	}
	std::tuple<int , int> gotoPath2 = algorithm->path[ algorithm->path.size ( ) - 1 ];
	std::tie ( Lastgoalx , Lastgoaly ) = gotoPath2;
	if ( path_now_x == Lastgoalx && path_now_z == Lastgoaly ) {
		std::cout << "GOAL IN1" << std::endl;
		return true;
	}


	if ( path_now_x == goalx && path_now_z == goaly ) {
		if ( algorithm->path.size ( ) - 1 > pathindex ) {
			pathindex += 1;
		}
		else {
			std::cout << "GOAL IN2" << std::endl;
			return true;
		}

	}
	else {
		float speed = 20.0f; // 이동 속도
		float deltaTime = Time::DeltaTime ( );
		float rotationSpeed = 5.0f; // 회전 속도

		glm::vec3 targetPosition ( ( goalx * 3 ) + 1.5f , Pos.y , -( ( goaly * 3 ) + 1.5f ) );
		glm::vec3 direction = targetPosition - Pos;

		// 방향 벡터 정규화
		if ( glm::length ( direction ) > 0.0f ) {
			direction = glm::normalize ( direction );
		}

		// 현재 방향 계산
		glm::vec3 currentDir = glm::normalize ( quaternion * glm::vec3 ( 0.0f , 0.0f , -1.0f ) );

		// 목표 방향과 현재 방향 사이의 각도 계산
		float dotProduct = glm::dot ( currentDir , direction );
		float angle = acos ( glm::clamp ( dotProduct , -1.0f , 1.0f ) ); // acos 값은 라디안 단위

		// 목표 방향 쿼터니언 계산
		glm::quat targetQuat;
		if ( glm::length ( direction ) > 0.0f ) {
			targetQuat = glm::quatLookAt ( direction , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
		}
		else {
			targetQuat = glm::quat ( 1.0f , 0.0f , 0.0f , 0.0f ); // 기본 쿼터니언
		}

		// 현재 쿼터니언과 목표 쿼터니언 사이를 SLERP로 보간 (회전)
		if ( angle > glm::radians ( 15.0f ) ) { // 각도 차이가 5도 이상인 경우 회전
			quaternion = glm::slerp ( quaternion , targetQuat , deltaTime * rotationSpeed );
		}
		else {
			// 각도 차이가 작으면 이동
			Pos += currentDir * speed * deltaTime;
		}

	}
	return false;
}


bool character::StaticAlgorithm ( glm::ivec2 _path )
{
	Path_now ( );

	if ( algorithm->RenewTime2 ( _path ) ) {
		algorithm->A_star ( );
		pathindex = 0;
	}

	int goalx = 0;
	int goaly = 0;

	int Lastgoalx = 0;
	int Lastgoaly = 0;

	if ( algorithm->path.size ( ) > 0 ) {
		std::tuple<int , int> gotoPath = algorithm->path[ pathindex ];
		std::tie ( goalx , goaly ) = gotoPath;
	}
	else {
		std::cout << "NOT PATH IS RENEW" << std::endl;
		return false;
	}
	std::tuple<int , int> gotoPath2 = algorithm->path[ algorithm->path.size ( ) - 1 ];
	std::tie ( Lastgoalx , Lastgoaly ) = gotoPath2;
	if ( path_now_x == Lastgoalx && path_now_z == Lastgoaly ) {
		std::cout << "GOAL IN1" << std::endl;
		return true;
	}


	if ( path_now_x == goalx && path_now_z == goaly ) {
		if ( algorithm->path.size ( ) - 1 > pathindex ) {
			pathindex += 1;
		}
		else {
			std::cout << "GOAL IN2" << std::endl;
			return true;
		}

	}
	else {
		float speed = 12.0f; // 이동 속도
		float deltaTime = Time::DeltaTime ( );
		float rotationSpeed = 5.0f; // 회전 속도

		glm::vec3 targetPosition ( ( goalx * 3 ) + 1.5f , Pos.y , -( ( goaly * 3 ) + 1.5f ) );
		glm::vec3 direction = targetPosition - Pos;

		// 방향 벡터 정규화
		if ( glm::length ( direction ) > 0.0f ) {
			direction = glm::normalize ( direction );
		}

		// 현재 방향 계산
		glm::vec3 currentDir = glm::normalize ( quaternion * glm::vec3 ( 0.0f , 0.0f , -1.0f ) );

		// 목표 방향과 현재 방향 사이의 각도 계산
		float dotProduct = glm::dot ( currentDir , direction );
		float angle = acos ( glm::clamp ( dotProduct , -1.0f , 1.0f ) ); // acos 값은 라디안 단위

		// 목표 방향 쿼터니언 계산
		glm::quat targetQuat;
		if ( glm::length ( direction ) > 0.0f ) {
			targetQuat = glm::quatLookAt ( direction , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
		}
		else {
			targetQuat = glm::quat ( 1.0f , 0.0f , 0.0f , 0.0f ); // 기본 쿼터니언
		}

		// 현재 쿼터니언과 목표 쿼터니언 사이를 SLERP로 보간 (회전)
		if ( angle > glm::radians ( 15.0f ) ) { // 각도 차이가 5도 이상인 경우 회전
			quaternion = glm::slerp ( quaternion , targetQuat , deltaTime * rotationSpeed );
		}
		else {
			// 각도 차이가 작으면 이동
			Pos += currentDir * speed * deltaTime;
		}


	}


	return false;
}




void character::Status_Machine ( )
{
	ApplySoundAttenuation (this->GetPos(),CollisionManager::getInstance().ReturnPlayer() );


	if ( phase == Phase::Idle ) {
		std::cout << "Idle : ";
		if ( action == Action::Idle ) {
			std::cout << "Idle";
			if ( status == Status::start ) {
				animator->PlayAnimation ( idleAnim );
				time = 0.0f;
				status = Status::running;
				std::cout << "나는 산기대의 오승원이다@@@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;
				SoundManager::getInstance ( ).GetSoundID ( "Chase1" )->PauseSound ( );
				SoundManager::getInstance ( ).GetSoundID ( "Chase2" )->PauseSound ( );
				
			}
			else if ( status == Status::running ) {
				
				time += Time::DeltaTime ( );
				

				if ( time > 4.0f ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				action = Action::walk;
				status = Status::start;
			}

		}
		if ( action == Action::running ) {
			std::cout << "running";
			if ( status == Status::start ) {
				animator->PlayAnimation ( runAnim );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->ReplaySound (volume );
				status = Status::running;

				
			}
			else if ( status == Status::running ) {
				if ( StaticAlgorithm ( StaticPaths[ Cycleindex ] ) ) {
					std::cout << "#############################Reached point: "
						<< StaticPaths[ Cycleindex ].x << ", "
						<< StaticPaths[ Cycleindex ].y << std::endl;

					// 다음 경로로 이동 (순환)
					Cycleindex = ( Cycleindex + 1 ) % StaticPaths.size ( );
					status = Status::exit;
				}
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->SetVolume ( volume );
			}
			else if ( status == Status::exit ) {
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->PauseSound ( );
				status = Status::start;
			}

		}
		if ( action == Action::walk ) {
			std::cout << "walk";
			if ( status == Status::start ) {
				animator->PlayAnimation ( walkAnim );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->ReplaySound ( );
				std::cout << "나는 정왕의 오승원이다@@@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;
				Cycleindex = ( Cycleindex + 1 ) % StaticPaths.size ( );
				//Cycleindex += 1;
				Path_now ( StaticPaths[ Cycleindex ] , path );

				status = Status::running;
			}
			else if ( status == Status::running ) {
				if ( StaticAlgorithm ( path ) ) {
					std::cout << "나는 시흥의 오승원이다@@@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;

					// 다음 경로로 이동 (순환)
					
					status = Status::exit;
				}
				std::cout << "나는 겜사의 오승원이다 지금 소리를 알려주지 : "<<volume << std::endl;
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->SetVolume ( volume );
			}
			else if ( status == Status::exit ) {
				std::cout << "나는 송파의 오승원이다@@@@@@@@@@@@@@@@@@@@@@@@ "<< std::endl;
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->PauseSound (  );
				status = Status::start;
				action = Action::Idle;
			}

		}
		if ( action == Action::attack ) {
			std::cout << "attack";
			if ( status == Status::start ) {
				animator->PlayAnimation ( attackAnim );
				status = Status::running;
			}
			else if ( status == Status::running ) {

			}
			else if ( status == Status::exit ) {

			}

		}
		if ( action == Action::scream ) {
			std::cout << "scream";
			if ( status == Status::start ) {
				animator->PlayAnimation ( sceramAnim );
				status = Status::running;
			}
			else if ( status == Status::running ) {

			}
			else if ( status == Status::exit ) {

			}

		}


		std::cout<<std::endl;

	}
	if ( phase == Phase::Angry ) {
		std::cout << "ANGRY : ";
		if ( action == Action::Idle ) {
			std::cout << "Idle";
			if ( status == Status::start ) {
				animator->PlayAnimation ( idleAnim );
				time = 0.0f;
				status = Status::running;

			}
			else if ( status == Status::running ) {

				time += Time::DeltaTime ( );


				if ( time > 4.0f ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				action = Action::walk;
				status = Status::start;
			}

		}
		if ( action == Action::running ) {
			std::cout << "running";
			if ( status == Status::start ) {
				animator->PlayAnimation ( runAnim );
				SoundManager::getInstance ( ).GetSoundID ( "Chase1" )->ReplaySound ( );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Foot" )->ReplaySound ( volume );
				status = Status::running;
			}
			else if ( status == Status::running ) {
				if( StaticAlgorithm ( chaseWhere ) ) {
					std::cout <<"나는 바보" << chaseWhere.x << "   " << chaseWhere.y << std::endl;
					status = Status::exit;
				}
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Foot" )->SetVolume ( volume );
				
				
			}
			else if ( status == Status::exit ) {
				
				action = Action::attack;
				status = Status::start;
			}

		}
		if ( action == Action::walk ) {
			std::cout << "walk";
			if ( status == Status::start ) {
				animator->PlayAnimation ( walkAnim );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->ReplaySound ( );
				
				Cycleindex = ( Cycleindex + 1 ) % StaticPaths.size ( );
				//Cycleindex += 1;
				Path_now ( StaticPaths[ Cycleindex ] , path );

				status = Status::running;
			}
			else if ( status == Status::running ) {
				if ( StaticAlgorithm ( path ) ) {
					

					// 다음 경로로 이동 (순환)

					status = Status::exit;
				}
				
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->SetVolume ( volume );
			}
			else if ( status == Status::exit ) {
				
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Walk" )->PauseSound ( );
				status = Status::start;
				action = Action::Idle;
			}

		}
		if ( action == Action::attack ) {
			std::cout << "attack";
			if ( status == Status::start ) {
				animator->PlayAnimation ( attackAnim );
				status = Status::running;
				time = 0.0f;
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if ( time>3.0f) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				chase = 0;
				action = Action::Idle;
				status = Status::start;
			}

		}
		if ( action == Action::scream ) {
			std::cout << "scream";
			if ( status == Status::start ) {
				animator->PlayAnimation ( sceramAnim );
				status = Status::running;
				time = 0.0f;
				SoundManager::getInstance ( ).GetSoundID ( "Roar" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if ( time>3.0f ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				status = Status::start;
				action = Action::running;
			}

		}



		std::cout << std::endl;
	}

	if ( phase == Phase::Mad ) {
		std::cout << "Mad : ";
		if ( action == Action::running ) {
			std::cout << "running";
			if ( status == Status::start ) {
				animator->PlayAnimation ( runAnim );
				time = 0.0f;
				status = Status::running;
				SoundManager::getInstance ( ).GetSoundID ( "Chase2" )->ReplaySound (0.3f);
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Run" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {
				
				if ( DynamicAlgorithm ( ) ) {
				
					action = Action::attack;
					status = Status::start;
				}

				time += Time::DeltaTime ( );
				if ( time > 12.0f  ) {
					
					time = 0.0f;
					status = Status::exit;
				}
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Run" )->SetVolume ( volume );
				
			}
			else if ( status == Status::exit ) {
				phase = Phase::Idle;
				action = Action::Idle;
				status = Status::start;
			}

		}

		if ( action == Action::attack ) {
			std::cout << "attack";
			if ( status == Status::start ) {
				animator->PlayAnimation ( attackAnim );
				status = Status::running;
				time = 0.0f;
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if ( time > 1.2f ) {

					time = 0.0f;
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {

				action = Action::running;
				status = Status::start;
			}

		}
		if ( action == Action::scream ) {
			std::cout << "scream";
			if ( status == Status::start ) {
				animator->PlayAnimation ( sceramAnim );
				status = Status::running;
				time = 0.0f;
				SoundManager::getInstance ( ).GetSoundID ( "Roar" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if(time >3.0f ){
				status = Status::exit;}
			}
			else if ( status == Status::exit ) {
				action = Action::running;
				status = Status::start;
			}

		}
		std::cout << std::endl;
		
	}
	if ( phase == Phase::Crazy ) {

		std::cout << "Crazy : ";
		if ( action == Action::running ) {
			std::cout << "running";
			if ( status == Status::start ) {
				animator->PlayAnimation ( runAnim );
				time = 0.0f;
				status = Status::running;
				SoundManager::getInstance ( ).GetSoundID ( "Chase2" )->ReplaySound ( 0.3f );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Run" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {

				if ( DynamicAlgorithm ( ) ) {

					action = Action::attack;
					status = Status::start;
				}

				SoundManager::getInstance ( ).GetSoundID ( "Monster_Run" )->SetVolume ( volume );

			}
			else if ( status == Status::exit ) {

			}

		}

		if ( action == Action::attack ) {
			std::cout << "scream";
			if ( status == Status::start ) {
				animator->PlayAnimation ( sceramAnim );
				status = Status::running;
				time = 0.0f;
				SoundManager::getInstance ( ).GetSoundID ( "Roar" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if ( time > 3.0f ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				action = Action::running;
				status = Status::start;
			}

		}
		if ( action == Action::scream ) {
			std::cout << "scream";
			if ( status == Status::start ) {
				animator->PlayAnimation ( sceramAnim );
				status = Status::running;
				time = 0.0f;
				SoundManager::getInstance ( ).GetSoundID ( "Roar" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {
				time += Time::DeltaTime ( );
				if ( time > 3.0f ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {
				action = Action::running;
				status = Status::start;
			}

		}
		std::cout << std::endl;


	}
	

	auto p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );
	auto p2 = Pos;
	
	if ( phase == Phase::Idle || phase == Phase::Angry ) {
		
		if ( distance1 >= ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) + ( ( p2.z - p1.z ) * ( p2.z - p1.z ) ) ) {


			phase = Phase::Mad;
			action = Action::scream;
			status = Status::start;

			
		}
	}
	else if (  phase == Phase::Mad ) {

		if ( distance2 >= ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) + ( ( p2.z - p1.z ) * ( p2.z - p1.z ) ) ) {

			time = 0.0f;

		}
		
	}
}
//
//idle:
//정적탐색 = > 두리번거리기
//walk = > idle
//
//angry :
//소리 지르기 = > 라이트달리기 = > 공격 = > 두리번 거리기 = > 정적탐색 = > 두리번거리기
//scream = > running->attack = > Idle = > walk = > 반복 ( 준 Idle상태 )
//
//mad:
//소리 지르기 = > 동적달리기 = > ( 12초 후 idle or 공격 )
//scream = > running -> 12초후 Idle