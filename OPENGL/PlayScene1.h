#pragma once
#include "Scene.h"
#include "Layer.h"
#include "character.h"


class PlayScene1 : public Scene {
public:
	PlayScene1 ( ) {}
	~PlayScene1 ( ) {}
	void Initialize ( ) {
		//Layer1 추가
		Layer* layer = new Layer ( );
		AddLayer ( layer );
		layer->AddGameobjects ( new character );	//해당 Layer에 gameobject 추가



	}


private:

};