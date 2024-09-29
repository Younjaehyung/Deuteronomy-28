#pragma once
#include "Scene.h"


class SceneManager {
private:
	std::vector <Scene*> Scenes;
public:
	void Update ( )
	{
		for ( auto& _Scene : Scenes ) {
			_Scene->Update ( );
		}
	}

	void Initialize ( )
	{
		for ( auto& _Scene : Scenes ) {
			_Scene->Initialize ( );
		}
	}

	void FixedUpdate ( )
	{
		for ( auto& _Scene : Scenes ) {
			_Scene->FixedUpdate ( );
		}
	}

	void Render ( )
	{
		for ( auto& _Scene : Scenes ) {
			_Scene->Render ( );
		}

	}

};