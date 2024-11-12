#include "Map.h"

void Map::Update ( )
{
}

void Map::Render ( const Program* program )
{   

    _model->Draw ( program );
}


void Map::Initialize ( const std::string& strName )
{
	_model = Model::Load ( strName );

    if ( !_model ) {
        std::cerr << "program UserSetError id : " << _model->Get ( ) << std::endl;
        return;


    }
}
