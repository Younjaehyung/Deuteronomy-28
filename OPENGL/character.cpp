#include "character.h"
#include "Time.h"
#include  "LightManager.h"
#include "Sound.h"

void character::Update ( )
{
	animator->UpdateAnimation ( Time::DeltaTime ( ) );
	//Algorithm ( );
	Status_Machine ( );
	/*Dir2 = camera->GetFront ( );
	Dir = camera->GetDir ( );*/
	//camera->Camera_Ismoving ( movestat );
	//카메라 흔들림 주석형

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
		float speed = 10.0f; // 이동 속도
		float deltaTime = Time::DeltaTime ( );
		float t = deltaTime*5.0f; // 보간 비율

		glm::vec3 direction = glm::vec3 ( 0.0f );

		// 목표 위치로의 방향 벡터 계산
		if ( Pos.x < (goalx*3) +1.5 ) {
			direction.x = 1.0f;
		}
		else if ( Pos.x > ( goalx * 3 ) + 1.5 ) {
			direction.x = -1.0f;
		}

		if ( Pos.z > -(( goaly * 3 ) + 1.5) ) {
			direction.z = -1.0f;
		}
		else if ( Pos.z < -( ( goaly * 3 ) + 1.5 )) {
			direction.z = 1.0f;
		}

		direction = glm::normalize ( direction );

		// 현재 위치와 목표 위치 사이를 선형 보간을 통해 이동
		Pos += direction * speed * deltaTime;

		// 목표 방향 쿼터니언 계산
		glm::quat targetQuat = glm::quatLookAt ( direction , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );

		// 현재 쿼터니언과 목표 쿼터니언 사이를 SLERP로 보간
		quaternion = Slerp ( quaternion , targetQuat , t );


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
				status = Status::running;
				
			}
			else if ( status == Status::running ) {
				if ( StaticAlgorithm ( chaseWhere ) ) {
					status = Status::exit;
				}

				status = Status::exit;
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
				status = Status::running;
			}
			else if ( status == Status::running ) {
				if ( StaticAlgorithm ( glm::ivec2 ( 12 , 18 ) ) ) {
					status = Status::exit;
				}
			}
			else if ( status == Status::exit ) {

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
				
				DynamicAlgorithm ( );

				time += Time::DeltaTime ( );
				if ( time > 12.0f ) {
					
					time = 0;
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
				SoundManager::getInstance ( ).GetSoundID ( "Chase2" )->ReplaySound ( 0.7f );
				SoundManager::getInstance ( ).GetSoundID ( "Monster_Run" )->ReplaySound ( );
			}
			else if ( status == Status::running ) {

				DynamicAlgorithm ( );

				time += Time::DeltaTime ( );
				if ( time > 12.0f ) {

					time = 0;
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

	
	if ( phase == Phase::Idle || phase == Phase::Angry ) {
		auto p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );
		auto p2 = Pos;
		if ( distance >= ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) + ( ( p2.z - p1.z ) * ( p2.z - p1.z ) ) ) {

			phase = Phase::Mad;
			action = Action::scream;
			status = Status::start;
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