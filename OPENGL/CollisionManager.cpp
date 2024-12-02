#include "CollisionManager.h"
#include "CameraManager.h"

void CollisionManager::Update ( std::vector<Object*>& colliders ) {
	collider = colliders;
	for ( size_t i = 0; i < collider.size ( ); ++i ) {
		for ( size_t j = i + 1; j < collider.size ( ); ++j ) {
			Object* obj1 = collider[ i ];
			Object* obj2 = collider[ j ]; 

			eLayerType type1 = obj1->GetObjectID ( ); // 객체의 레이어 타입 반환
			eLayerType type2 = obj2->GetObjectID ( );


			if ( ShouldCollide ( type1 , type2 ) ) {	//충돌이 가능한 객체냐?
				if ( Check_AABB_Collision ( obj1 , obj2 ) ) {	//충돌 했냐?
					obj1->HandleCollision ( obj2 );
					obj2->HandleCollision ( obj1 );
					std:: cout << obj1->name << " " << obj2->name << std::endl;
				}
			}
		}
	}
}

bool CollisionManager::ShouldCollide ( eLayerType type1 , eLayerType type2 ) {

	return mCollisionLayerMatrix[ ( uint32_t ) type1 ].test ( ( uint32_t ) type2 );
}



void CollisionManager::Render ( ) {
	//RenderBox ( playerBox ); // 플레이어 충돌 박스 렌더링
	//RenderBox ( monsterBox ); // 몬스터 충돌 박스 렌더링
	world_coord_render ( );
}


bool CollisionManager::Check_Collider (const std::string& name1, const std::string& name2 ) {
	for ( auto object1 : collider ) {
		object1->Pos ;
	}

	return true;



	return false;
}

void CollisionManager::Initialize ( ){	


	world_coord_init ( );
	InitializeCollisionMatrix ( );
}


void CollisionManager::InitializeCollisionMatrix ( ) {
	// Player와 충돌하는 레이어 설정
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Player ].set ( ( uint32_t ) eLayerType::Enemy );
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Player ].set ( ( uint32_t ) eLayerType::Environment );
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Player ].set ( ( uint32_t ) eLayerType::Light );
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Player ].set ( ( uint32_t ) eLayerType::Item );

	// Enemy와 충돌하는 레이어 설정
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Enemy ].set ( ( uint32_t ) eLayerType::Player );
	mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Light ].set ( ( uint32_t ) eLayerType::Player );
	//mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Enemy ].set ( ( uint32_t ) eLayerType::Light );

	// Projectile과 충돌하는 레이어 설정
	//mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Projectile ].set ( ( uint32_t ) eLayerType::Enemy );
	//mCollisionLayerMatrix[ ( uint32_t ) eLayerType::Projectile ].set ( ( uint32_t ) eLayerType::Environment );

	// Environment는 어떤 것도 충돌하지 않음
}



void CollisionManager::SetBox (Object* object ) {

}

void CollisionManager::Observer ( )
{

	
}


bool CollisionManager::Check_AABB_Collision ( Object* box1 , Object* box2 ) {


	glm::vec3 box1_min = box1->GetPos ( ) - ( box1->GetBox ( ).Size * 0.5f );
	glm::vec3 box1_max = box1->GetPos ( ) + ( box1->GetBox ( ).Size * 0.5f );

	glm::vec3 box2_min = box2->GetPos ( ) - ( box2->GetBox ( ).Size * 0.5f );
	glm::vec3 box2_max = box2->GetPos ( ) + ( box2->GetBox ( ).Size * 0.5f );

	return ( box1_min.x <= box2_max.x && box1_max.x >= box2_min.x &&
			box1_min.y <= box2_max.y && box1_max.y >= box2_min.y &&
			box1_min.z <= box2_max.z && box1_max.z >= box2_min.z );
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
