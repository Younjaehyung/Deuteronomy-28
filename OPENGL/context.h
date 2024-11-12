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
#include "framebuffer.h"

CLASS_PTR(Context)

struct Light {
	glm::vec3 direction{ glm::vec3 ( -0.2f, -1.0f, -0.3f ) };	//Directional Light
	glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };	//Spot Light 보이는 부분
	float distance{ 32.0f }; //Point Light 감쇠 거리

	glm::vec3 position{ glm::vec3 ( 3.0f, 3.0f, 3.0f ) }; //광원의 위치
	glm::vec3 ambient{ glm::vec3 ( 0.1f, 0.1f, 0.1f ) };  //광원의 색
	glm::vec3 diffuse{ glm::vec3 ( 0.5f, 0.5f, 0.5f ) };  //오브젝트의 색
	glm::vec3 specular{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };
};

class Context{
public:
	static ContextUPtr Create ( );
	void Update ( );
	void Render ( );
	void ProcessInput ( GLFWwindow* window );

	
	void Reshape ( int width , int height );

	void MouseButton ( int button , int action , double x , double y );

private:
	Context ( ) {};
	bool Init ( );
	
	std::vector<Light> Lights;

	Camera* mainCamera;
	glm::mat4 Camera_Transform;

	Player* player;




	//.vs .fs 프로그램 쉐이더 코드
	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_textureProgram;

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

	//model
	ModelUPtr map;

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
	

	glm::vec3 m_cameraPos{ glm::vec3 ( -10.0f, 3.0f, 3.0f ) };	//카메라의 위치
	glm::vec3 m_cameraFront{ glm::vec3 ( 0.0f, 0.0f, -1.0f ) };	//카메라가 보고 있는 방향
	glm::vec3 m_cameraUp{ glm::vec3 ( 0.0f, 1.0f, 0.0f ) };		//카메라 up벡터

	glm::vec4 m_clearColor{ glm::vec4 ( 0.1f, 0.2f, 0.3f, 0.0f ) };


	//빛
	
	Light m_light;

	

	
	bool m_animation{ true };	//애니메이션 사용 여부
	bool m_cameraControl{ false };	//카메라 사용 여부 (우클릭)

	//창크기
	int m_width{ 640 };
	int m_height{ 480 };
};

