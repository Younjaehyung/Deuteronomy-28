#include "CollisionManager.h"
#include "CameraManager.h"

void CollisionManager::Update ( ) {
	for ( auto object : collider ) {
		if ( object->name == "player" ) {
			playerBox.center = object->Pos;
			playerBox.size = glm::vec3 ( 5.0f , 6.0f , 5.0f ); // 폭, 높이, 깊이
		}
		else if ( object->name == "monster" ) {
			monsterBox.center = object->Pos;
			monsterBox.size = glm::vec3 ( 5.0f , 6.0f , 5.0f ); // 폭, 높이, 깊이
		}
		//else if ( object->name == "item" ) {
		//	monsterBox.center = object->Pos;
		//	monsterBox.size = glm::vec3 ( 3.0f , 3.0f , 3.0f ); // 폭, 높이, 깊이
		//}
	}

	// 충돌 검사
	if ( Check_AABB_Collision ( playerBox , monsterBox ) ) {
		std::cout << "Collision!!Collision!!Collision!!Collision!!Collision!!" << std::endl;
		std::cout << "Collision!!Collision!!Collision!!Collision!!Collision!!" << std::endl;
		std::cout << "Collision!!Collision!!Collision!!Collision!!Collision!!" << std::endl;
	}
	//else if ( Check_AABB_Collision ( playerBox , itemBox ) ) {
	//	std::cout << "item 겟또다제" << std::endl;
	//}
}

void CollisionManager::RenderBox ( const CollisionBox& box ) {
	glm::vec3 halfSize = box.size * 0.5f;

	// 충돌 박스의 8개 꼭짓점 계산
	std::vector<glm::vec3> vertices = {
		box.center + glm::vec3 ( -halfSize.x, -halfSize.y, -halfSize.z ),
		box.center + glm::vec3 ( halfSize.x, -halfSize.y, -halfSize.z ),
		box.center + glm::vec3 ( halfSize.x,  halfSize.y, -halfSize.z ),
		box.center + glm::vec3 ( -halfSize.x,  halfSize.y, -halfSize.z ),
		box.center + glm::vec3 ( -halfSize.x, -halfSize.y,  halfSize.z ),
		box.center + glm::vec3 ( halfSize.x, -halfSize.y,  halfSize.z ),
		box.center + glm::vec3 ( halfSize.x,  halfSize.y,  halfSize.z ),
		box.center + glm::vec3 ( -halfSize.x,  halfSize.y,  halfSize.z )
	};

	// 충돌 박스의 선 연결을 위한 인덱스
	std::vector<uint32_t> indices = {
		0, 1, 1, 2, 2, 3, 3, 0, // 아래면
		4, 5, 5, 6, 6, 7, 7, 4, // 윗면
		0, 4, 1, 5, 2, 6, 3, 7  // 세로 연결
	};

	// OpenGL 버퍼 생성 및 바인딩
	GLuint vertexBuffer , indexBuffer;
	glGenBuffers ( 1 , &vertexBuffer );
	glBindBuffer ( GL_ARRAY_BUFFER , vertexBuffer );
	glBufferData ( GL_ARRAY_BUFFER , vertices.size ( ) * sizeof ( glm::vec3 ) , vertices.data ( ) , GL_DYNAMIC_DRAW );

	glGenBuffers ( 1 , &indexBuffer );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , indexBuffer );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER , indices.size ( ) * sizeof ( uint32_t ) , indices.data ( ) , GL_DYNAMIC_DRAW );

	// 위치 속성 활성화
	glEnableVertexAttribArray ( 0 );
	glVertexAttribPointer ( 0 , 3 , GL_FLOAT , GL_FALSE , sizeof ( glm::vec3 ) , ( void* ) 0 );

	// 색상 설정 (예: 노란색)
	glColor3f ( 1.0f , 1.0f , 0.0f ); // RGB: 노란색

	// 선 그리기
	glDrawElements ( GL_LINES , indices.size ( ) , GL_UNSIGNED_INT , 0 );

	// 버퍼 해제
	glDeleteBuffers ( 1 , &vertexBuffer );
	glDeleteBuffers ( 1 , &indexBuffer );
}

void CollisionManager::Render ( ) {
	//RenderBox ( playerBox ); // 플레이어 충돌 박스 렌더링
	//RenderBox ( monsterBox ); // 몬스터 충돌 박스 렌더링
	world_coord_render ( );
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


bool CollisionManager::Check_AABB_Collision ( const CollisionBox& box1 , const CollisionBox& box2 ) {
	return ( box1.center.x - box1.size.x * 0.5f <= box2.center.x + box2.size.x * 0.5f &&
			box1.center.x + box1.size.x * 0.5f >= box2.center.x - box2.size.x * 0.5f &&
			box1.center.y - box1.size.y * 0.5f <= box2.center.y + box2.size.y * 0.5f &&
			box1.center.y + box1.size.y * 0.5f >= box2.center.y - box2.size.y * 0.5f &&
			box1.center.z - box1.size.z * 0.5f <= box2.center.z + box2.size.z * 0.5f &&
			box1.center.z + box1.size.z * 0.5f >= box2.center.z - box2.size.z * 0.5f );
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
	//std::cout <<sizeof( m_world_matrix_vertex) << std::endl;
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
