#include "CollisionManager.h"
#include "CameraManager.h"

void CollisionManager::Update ( )
{

}

void CollisionManager::SetCollision (Object* collider_box )
{
	collider.push_back ( collider_box );

}

bool CollisionManager::Check_Collider (const std::string& name1, const std::string& name2 ) {
	for ( auto object1 : collider ) {
		object1->Pos ;
	}

	return true;



	return false;
}

void CollisionManager::Initialize ( )
{
	world_coord_init ( );
}



void CollisionManager::SetBox (Object* object ) {
	//glm::vec3 Dir = glm::normalize( glm::vec3(object->Dir2.x, 0.0f, object->Dir2.z) );
	glm::translate ( glm::mat4 ( 1.0f ) , object->Pos ) *object->Dir;
	//glm::rotate ( glm::mat4 ( 1.0f ),glm::radians( object->Dir),glm::vec3(1.0f,0.0f,0.0f ));
	
}

void CollisionManager::Observer ( )
{

	std::string name1 = "player";
	std::string name2 = "monster";


	
	
}

void CollisionManager::Render ( )
{
	world_coord_render ( );

}


void CollisionManager::world_coord_render (){
	//world 좌표츅/////////////////////


	m_world_coord->Use ( );
	m_world_vertexLayout->Bind ( );
	m_world_indexBuffer->Bind ( );

	auto ModelTransform =
		glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 1.0f ) );
	m_world_coord->SetUniform ( "transform" , CameraManager::getInstance ( ).Camera_transform ( ) * ModelTransform );

	glDrawElements ( GL_LINES , m_world_matrix_index.size() , GL_UNSIGNED_INT , 0 );
	///////////////////////////////////////////////////

}


void CollisionManager::world_coord_init ( ) {
	/////////world 좌표축//////////////////////////////////////////

	int gridSize = 50;
	float spacing = 3.0f;
	int numLines = gridSize + 1;
	float halfSize = ( gridSize * spacing ) / 2.0f;

	for ( int i = 0; i < numLines; ++i ) {
		float offset = -halfSize + i * spacing;

		// X축 방향 (Z축 일정)
		m_world_matrix_vertex.push_back ( -halfSize );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( offset );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 1.0f );
		m_world_matrix_vertex.push_back ( 0.0f );

		m_world_matrix_vertex.push_back ( halfSize );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( offset );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 1.0f );
		m_world_matrix_vertex.push_back ( 0.0f );

		// Z축 방향 (X축 일정)
		m_world_matrix_vertex.push_back ( offset );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( -halfSize );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 1.0f );

		m_world_matrix_vertex.push_back ( offset ); 
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( halfSize );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 0.0f );
		m_world_matrix_vertex.push_back ( 1.0f );
	}


	// 인덱스 데이터 생성
	
	for ( uint32_t i = 0; i < m_world_matrix_vertex.size ( ) / 6; ++i ) {
		m_world_matrix_index.push_back ( uint32_t(i) );
	}
	m_world_vertexLayout = VertexLayout::Create ( );
	// 버퍼 생성
	m_world_vertexBuffer = Buffer::CreateWithData (
		GL_ARRAY_BUFFER , GL_STATIC_DRAW , m_world_matrix_vertex.data ( ) , sizeof ( float ) , m_world_matrix_vertex.size ( )
	);
	std::cout <<sizeof( m_world_matrix_vertex) << std::endl;
	m_world_indexBuffer = Buffer::CreateWithData (
		GL_ELEMENT_ARRAY_BUFFER , GL_STATIC_DRAW , m_world_matrix_index.data ( ) , sizeof ( uint32_t ) ,  m_world_matrix_index.size ( )
	);

	// 레이아웃 설정
	
	m_world_vertexLayout->SetAttrib ( 0 , 3 , GL_FLOAT , GL_FALSE , sizeof ( float ) * 6 , 0 );
	m_world_vertexLayout->SetAttrib ( 1 , 3 , GL_FLOAT , GL_FALSE , sizeof ( float ) * 6 , 3 );


	/////////world 좌표축//////////////////////////////////////////
	m_world_coord = Program::Create ( "./shader/world_coord.vs" , "./shader/world_coord.fs" );
	Program::UserSetError ( m_world_coord );

	///////////////////////////////////////////////////
}
