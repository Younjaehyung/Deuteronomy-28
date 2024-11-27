#pragma once
#include "object.h"
#include "Player.h"


class CollisionManager
{
public:
	static CollisionManager& getInstance ( ) {
		static CollisionManager instance;
		return instance;
	}

	struct CollisionBox {
		glm::vec3 center;  // 중심 좌표
		glm::vec3 size;    // 크기 (폭, 높이, 깊이)
	};

	void Update ( );
	void SetCollision ( Object* collider_box );
	void Observer ( );
	void Render ( );
	void SetBox ( Object* object );
	void RenderBox ( const CollisionBox& box );
	bool Check_Collider ( const std::string& name1 , const std::string& name2 ); //안써도 될듯? 근데 혹시 모르니까 남겨둠
    virtual void Initialize ();
	bool Check_AABB_Collision ( const CollisionBox& box1 , const CollisionBox& box2 );


	glm::vec3 ReturnPlayer ( ) {
		for (auto player : collider ){
			if ( player->name == "player" ) {
				//std::cout << "Player" << std::endl;
				return player->Pos;
			}

		}

		return glm::vec3 ( 0 , 0 , 0 );
	}
	glm::vec3 ReturnMonster ( ) {

		for ( auto monster : collider ) {
			if ( monster->name == "monster" ) {
				return monster->Pos;
			}

		}
		return glm::vec3 ( 0 , 0 , 0 );
	}
	//glm::vec3 ReturnItem ( ) {		//아이템 추가되면 넣을꺼

	//	for ( auto item : collider ) {
	//		if ( item->name == "item" ) {
	//			return item->Pos;
	//		}

	//	}
	//	return glm::vec3 ( 0 , 0 , 0 );
	//}

	void world_coord_render ( );
	void world_coord_init ( );



private:
	CollisionManager ( ) {

	}

	std::vector<Object*> collider;
	Object* player;
	Object* monster;
	//Object* item;
	CollisionBox playerBox;
	CollisionBox monsterBox;
	//CollisionBox itemBox;

	struct Line {
		float x;
		float y;
	};

	int Map_Matrix[ 100 ][ 100 ] = {};

	ProgramUPtr m_world_coord;
	VertexLayoutUPtr m_world_vertexLayout;
	BufferUPtr m_world_vertexBuffer;
	BufferUPtr m_world_indexBuffer;
	std::vector<float> m_world_matrix_vertex;
	std::vector<uint32_t> m_world_matrix_index;
};

