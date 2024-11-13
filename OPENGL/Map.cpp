#include "Map.h"
#include "Time.h"


void Map::Update ( )
{
}

void Map::Render ( const Program* program )
{

		model->Draw ( program );
		ground->Draw ( program );
}


void Map::Initialize ( const std::string& strName )
{
	
	
	
	_model = Model::Load ( strName );
	ground = Mesh::CreatePlane ( );
    if ( !_model ) {
        std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
        return;


    }

	
}
