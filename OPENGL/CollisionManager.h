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

	void Update ( );
	void SetCollision ( Object* collider_box );
	void Observer ( );
	void Render ( );
	void SetBox ( Object* object );
	bool Check_Collider ( const std::string& name1 , const std::string& name2 );
    virtual void Initialize ();
	

	glm::vec3 ReturnPlayer ( ) {
		for (auto player : collider ){
			if ( player->name == "player" ) {
				std::cout << "Player" << std::endl;
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

	void world_coord_render ( );
	void world_coord_init ( );

private:
	CollisionManager ( ) {

	}

	std::vector<Object*> collider;
	Object* player;
	Object* monster;

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

