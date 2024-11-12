#pragma once
#include "Gameobject.h"
#include "model.h"

class GameMap :Gameobject
{
private:
	ModelUPtr m_model;
	

	
public:

	virtual void Initialize ( );
	virtual void Update ( );
	virtual void Render ( );

};

