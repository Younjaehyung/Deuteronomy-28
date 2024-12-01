#pragma once
#include "common_include.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "mesh_user.h"
#include "model.h"
#include "CameraManager.h"
#include "Player.h"
#include "Map.h"
#include "framebuffer.h"
#include "Animation.h"
#include "Animator.h"
#include "character.h"
#include "shadow.h"
#include "LightManager.h"
#include "Item.h"

CLASS_PTR(Context)
//빛


class Context{
public:
	static ContextUPtr Create ( );

	//게임 start


	//게임 play
	void Update ( );
	void Render ( );
	void ProcessInput ( GLFWwindow* window );
	void IMGUI_USER ( );
	void UIDraw ( );

	void Reshape ( int width , int height );
	void MainDraw ( glm::vec3 _pos , glm::mat4 _cameraTransform );


	void MouseButton ( int button , int action , double x , double y );


	void GameobjectUpdate ( ) {
		for ( auto& gameobject : obj ) {
			gameobject->Update ( );
		}
	}
	void GameobjectDelete ( ) {
		for ( auto it = obj.begin ( ); it != obj.end ( );) {
			if ( ( *it )->GetDestroy ( ) ) {
				delete* it;
				it = obj.erase ( it );
			}
			else {
				++it;
			}
		}
	}

	int m_width{ 640 };
	int m_height{ 480 };
private:
	Context ( ) {};
	bool Init ( );
	
	std::vector<Object*> obj;
	Camera* mainCamera;
	glm::mat4 Camera_Transform;
	LightMass* light1;
	Player* player;
	Map* map;
	character* object1;		//Neddlehead
	character* object2;		//Bagman
	Item* item;

	ProgramUPtr m_animationProgram;

	//.vs .fs 프로그램 쉐이더 코드

	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_simpleAnimationProgram;
	ProgramUPtr m_textureProgram;
	ProgramUPtr m_assimp_Program;
	ProgramUPtr m_lightingShadowProgram;
	//사용자 지정 프레임버퍼
	FramebufferUPtr m_framebuffer;

	
	//world 좌표계 축............
	ProgramUPtr m_world_coord;
	VertexLayoutUPtr m_world_vertexLayout;	
	BufferUPtr m_world_vertexBuffer;
	BufferUPtr m_world_indexBuffer;
	///////////////////////
	 
	// cubemap
	CubeTextureUPtr m_cubeTexture;
	ProgramUPtr m_skyboxProgram;
	ProgramUPtr m_envMapProgram;
	
	ShadowMapUPtr m_shadowMap;

	//VAO,VBO,ELM 버퍼 포인터
	MeshUPtr m_box;
	MeshUPtr m_plane;
	// material parameter
	MaterialPtr m_material;

	//마우스
	glm::vec2 m_prevMousePos{ glm::vec2 ( 0.0f ) };

	//카메라
	float m_cameraPitch{ 0.0f };
	float m_cameraYaw{ 0.0f };
	
	float nowTime=0.0f;

	glm::vec3 m_cameraPos{ glm::vec3 ( -10.0f, 3.0f, 3.0f ) };	//카메라의 위치
	glm::vec3 m_cameraFront{ glm::vec3 ( 0.0f, 0.0f, -1.0f ) };	//카메라가 보고 있는 방향
	glm::vec3 m_cameraUp{ glm::vec3 ( 0.0f, 1.0f, 0.0f ) };		//카메라 up벡터

	glm::vec4 m_clearColor{ glm::vec4 ( 0.1f, 0.2f, 0.3f, 0.0f ) };


	//빛
	
	struct Light {
		bool directional{ false };

		glm::vec3 direction{ glm::vec3 ( -0.2f, -1.0f, -0.3f ) };	//Directional Light
		glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };	//Spot Light 보이는 부분
		float distance{ 232.0f }; //Point Light 감쇠 거리

		glm::vec3 position{ glm::vec3 ( 3.0f, 3.0f, 3.0f ) }; //광원의 위치
		glm::vec3 ambient{ glm::vec3 ( 0.0f, 0.0f, 0.0f ) };  //광원의 색
		glm::vec3 diffuse{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };  //오브젝트의 색
		glm::vec3 specular{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };
	};
	Light m_light;

	glm::vec3 m_cameraD =  glm::vec3(0.0f);
	glm::vec3 m_cameraP = glm::vec3 ( 0.0f );
	glm::vec3 m_cameraU = glm::vec3 ( 0.0f );
	float m_cameraA = 45.0f;
	
	bool m_blinn{ true };	//blinn 쉐이더 사용여부
	bool m_animation{ true };	//애니메이션 사용 여부
	bool m_cameraControl{ false };	//카메라 사용 여부 (우클릭)

	//창크기
	
};

