#pragma once
#include "common_include.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "mesh_user.h"
#include "model.h"
#include "framebuffer.h"
class GameManager;
#include "Time.h"
#include "GameManager.h"
CLASS_PTR(Context)

class Context{
public:
	static ContextUPtr Create ( );
	void Render ( );
	void ProcessInput ( GLFWwindow* window );
	void Update ( );

	void Reshape ( int width , int height );
	void MouseMove ( double x , double y );
	void MouseButton ( int button , int action , double x , double y );

private:
	Context ( ) {};
	bool Init ( );
	
	
	template <typename T>
	void world_coord_render (T& ,T& );
	void world_coord_init ( );

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

	//Game
	GameManager* Game;
	


	//model
	ModelUPtr m_model;

	//VAO,VBO,ELM 버퍼 포인터
	MeshUPtr m_box;
	MeshUPtr m_plane;
	// material parameter
	MaterialPtr m_material;
     


	glm::vec4 m_clearColor{ glm::vec4 ( 0.1f, 0.2f, 0.3f, 0.0f ) };


	//빛
	struct Light {
		glm::vec3 direction{ glm::vec3 ( -0.2f, -1.0f, -0.3f ) };	//Directional Light
		glm::vec2 cutoff{ glm::vec2 ( 20.0f, 5.0f ) };	//Spot Light 보이는 부분
		float distance{ 32.0f }; //Point Light 감쇠 거리

		glm::vec3 position{ glm::vec3 ( 3.0f, 3.0f, 3.0f ) }; //광원의 위치
		glm::vec3 ambient{ glm::vec3 ( 0.1f, 0.1f, 0.1f ) };  //광원의 색
		glm::vec3 diffuse{ glm::vec3 ( 0.5f, 0.5f, 0.5f ) };  //오브젝트의 색
		glm::vec3 specular{ glm::vec3 ( 1.0f, 1.0f, 1.0f ) };
	};
	Light m_light;

	

	
	bool m_animation{ true };	//애니메이션 사용 여부
	bool m_cameraControl{ false };	//카메라 사용 여부 (우클릭)

	//창크기
	int m_width{ 640 };
	int m_height{ 480 };
};

