#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"
#include "LightMass.h"
#include "Scene.h"
#include "input.h"

class Deathmap :public Scene
{

	LightMass* light;

	MeshUPtr ground = Mesh::CreatePlane ( );
	ModelPtr m_map;
	ModelPtr _monster;
	Model* m_monster;
	Animation* monsterAnim;
	Animation* monster2Anim;
	UBOBUFFERUPtr MUBO;
	Animator* Manimator;
	Animator* Manima2tor;

	Model* m_player;
	ModelPtr _player;

	Animation* playerAnim;
	UBOBUFFERUPtr PUBO;
	Animator* Panimator;

	Camera* mapCamera;
	//std::vector<LightMass*> Visullight;
	float m_width=0.0f;
	float m_height=0.0f;
	float nowTime=0.0f;
	float animationDuration = 1.5f; // 애니메이션 지속 시간 (초)
	float elapsedTime = 0.0f; // 경과 시간
	int SoundToggle = 0;


	glm::vec3 LifePos{ 1.0f , 8.5f , -7.0f};
	glm::vec3 DeathPos{ 1.0f , 1.5f , -7.0f };

	glm::vec3 initialCameraPos = LifePos + glm::vec3 ( 1.0f , -0.1f , -2.0f ); // 초기 카메라 위치
	glm::vec3 finalCameraPos = DeathPos + glm::vec3 ( 1.0f , -0.1f , -2.0f ); // 최종 카메라 위치

	glm::quat initialCameraRot = glm::quatLookAt ( glm::normalize ( LifePos - initialCameraPos ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
	
	glm::quat zRotation = glm::angleAxis ( glm::radians ( 90.0f ) , glm::vec3 ( 0.0f , 0.0f , 1.0f ) );
	glm::quat finalCameraRot = glm::quatLookAt ( glm::normalize ( DeathPos - finalCameraPos ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) )* zRotation;

	glm::vec3 Cameramoving{ 7.0f , 5.0f , -3.0f };

	MeshUPtr m_plane;
	FramebufferPtr m_framebuffer;
	TextureUPtr CameraUITEXTURE;
	TextureUPtr BloodTEXTURE;
	TextureUPtr DIETEXTURE;

	Program* program;
	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
	ProgramUPtr m_cameraUIProgram;
	ProgramUPtr m_textureProgram;
	ProgramUPtr m_lightingProgram;
	ProgramUPtr m_AnimationProgram;
	
	int restart = 0;
	int status = 0;
	int attack = 0;
	float attack_time = 0.0f;
public:
	Deathmap () {
		typeID = 0;

		m_lightingProgram = Program::Create ( "./shader/lighting_shadow.vs" , "./shader/lighting_shadow.fs" );
		if ( !m_lightingProgram ) {
			//std::cerr << "program UserSetError id : " << m_lightingProgram->Get ( ) << std::endl;
			return;


		}

		m_AnimationProgram = Program::Create ( "./shader/animation.vs" , "./shader/animation.fs" );
		if ( !m_AnimationProgram ) {
			//std::cerr << "program UserSetError id : " << m_AnimationProgram->Get ( ) << std::endl;
			return ;

			
		}

		m_cameraUIProgram = Program::Create ( "./shader/cameraUI.vs" , "./shader/cameraUI.fs" );
		if ( !m_cameraUIProgram ) {
			//std::cerr << "program UserSetError id : " << m_cameraUIProgram->Get ( ) << std::endl;
			return;


		}

		m_simpleProgram = Program::Create ( "./shader/simple.vs" , "./shader/simple.fs" );
		if ( !m_simpleProgram ) {
			//std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
			return;


		}

		m_simpleAnimationProgram = Program::Create ( "./shader/simple_animation.vs" , "./shader/simple_animation.fs" );
		if ( !m_simpleAnimationProgram ) {
			//std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
			return;


		}

		m_textureProgram = Program::Create ( "./shader/texture.vs" , "./shader/texture.fs" );
		if ( !m_textureProgram ) {
			//std::cerr << "program UserSetError id : " << m_textureProgram->Get ( ) << std::endl;
			return;


		}
		// Z축 기준 90도 회전 추가

	
		m_plane = Mesh::CreatePlane ( );
		auto CameraUi = Image::Load ( "./model/UI/Camera.png" , false );
		CameraUITEXTURE = Texture::CreateFromImage ( CameraUi.get ( ) );

		auto blood = Image::Load ( "./model/UI/DieUI.png" , false );
		BloodTEXTURE = Texture::CreateFromImage ( blood.get ( ) );

		auto DIE = Image::Load ( "./model/UI/DIe.png" , true );
		DIETEXTURE = Texture::CreateFromImage ( DIE.get ( ) );
		light = new LightMass;
		light->SetLight ( glm::vec3 ( 10.0f , 12.0f , -16.0f ) , glm::normalize(glm::vec3(-9.0f,-1.0f,10.0f)) , glm::vec2 ( 30.0f , 15.0f ) );

		m_map = Model::Load ("./model/DeathBox.glb" );
		PUBO = UBOBUFFER::Create ( 200 );
		MUBO = UBOBUFFER::Create ( 200 );

		if ( CUTEMDOE == 0 ) {//25.09.23임시로 추가
			_monster = Model::Load ( "./model/HULK1/HulkBBoBBo.glb" );
			_player = Model::Load ( "./model/SibalGLB/SibalBbobbo.glb" );
		}
		else { //Cute
			_monster = Model::Load ( "./model/HULK1/HulkBBoBBo.glb" );
			_player = Model::Load ( "./model/SibalGLB/SibalBbobbo.glb" );
		}
		

		m_monster = _monster.get ( );
		m_player = _player.get ( );

		monsterAnim = new Animation ("./model/HULK1/HulkBBoBBo.glb" , m_monster );
		monster2Anim = new Animation ( "./model/HULK1/Hulk_Death.glb" , m_monster );
		playerAnim = new Animation ( "./model/SibalGLB/SibalBbobbo.glb" , m_player );
		Manima2tor = new Animator ( monster2Anim );
		Manimator = new Animator ( monsterAnim );
		Panimator = new Animator ( playerAnim );
		mapCamera = new Camera;
		mapCamera->SetCamera ( initialCameraPos , glm::vec3 ( -2.0f , 0.7f , 0.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
	}
	virtual void Update ( );
	virtual void Render ( );
	virtual void MainRender ( );
	virtual void shadowRender ( );
	virtual bool Initialize ();
	virtual void Reshape ( int width , int height ) {

		m_width = width;
		m_height = height;
		glViewport ( 0 , 0 , m_width , m_height );

		if ( m_width <= 1 ) {
			m_width = 1;
		}
		if ( m_height <= 1 ) {
			m_height = 1;
		}
		//std::cout << m_height << std::endl;
		//사용자 정의 프레임버퍼 생성
		m_framebuffer = Framebuffer::Create ( Texture::Create ( m_width , m_height , GL_RGBA ) );

	}

	void ProcessInput ( GLFWwindow* window )
	{

		if (input::GetKeyDown ( eKeyCode::SPACE )) {
			restart = 1;
		}
	}

	virtual int Check ( ) {
		if (restart) {
			restart = 0;
			return 1;
		}

		return 0;
	}

};

