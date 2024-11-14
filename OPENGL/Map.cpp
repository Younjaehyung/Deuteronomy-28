#include "Map.h"
#include "Time.h"


void Map::Update ( )
{
}

void Map::Render ( const Program* program )
{

		_model->Draw ( program );

		program->SetUniform ( "transform" , CameraManager::getInstance().Camera_transform()*glm::rotate( glm::mat4 ( 1.0f ),glm::radians(90.0f ),glm::vec3(1.0f,0.0f,0.0f) )
			*glm::scale ( glm::mat4 ( 1.0f ) ,glm::vec3(100.0f,100.0f,100.0f) ) );
		ground->Draw ( program );
}


void Map::Initialize ( const std::string& strName )
{
	
	
	ground = Mesh::CreatePlane ( );
	_model = Model::Load ( strName );
	std::cerr << "MAPAA" << std::endl;
	
    if ( !_model ) {
        std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
        return;


    }

	
}
