#pragma once
#include "Layer.h"


class Scene {
private:
	std::vector <Layer*> Layers;
public:
	Scene ( );
	virtual ~Scene ( );

	virtual void Update ( )
	{
		for ( auto& _Layer : Layers ) {
			_Layer->Update ( );
		}
	}

	virtual void Initialize ( )
	{
		for ( auto& _Layer : Layers ) {
			_Layer->Initialize ( );
		}
	}

	virtual void AddScene ( Layer* addscene )
	{
		Layers.push_back ( addscene );
	}

	virtual void FixedUpdate ( )
	{
		for ( auto& _Layer : Layers ) {
			_Layer->FixedUpdate ( );
		}
	}

	virtual void Render ( )
	{
		for ( auto& _Layer : Layers ) {
			_Layer->Render ( );
		}

	}

};