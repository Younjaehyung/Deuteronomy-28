#pragma once
#include "Actor.h"
#include "Component.h"
#include <vector>


class Scene {
private:
	std::vector <Actor*> Gameobjects;
public:

	void Update ( )
	{
		for (auto& _Gameobject : Gameobjects ) {
			_Gameobject->Update ( );
		}
	}

	void Initialize ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			
		}
	}

	void FixedUpdate ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			_Gameobject->FixedUpdate ( );
		}
	}

	void AddGameobjects ( const Actor* actor ) {
		Gameobjects.push_back ( actor );
	}

	void Render ( )
	{
		for ( auto& _Gameobject : Gameobjects ) {
			_Gameobject->Render ( );
		}

	}

};