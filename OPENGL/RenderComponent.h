#pragma once
#include "Component.h"
#include "image.h"
#include "model.h"


class RenderComponent : public Component {
private:
	ModelUPtr _model;
	ImageUPtr _image;
	ProgramUPtr _shader;
	glm::mat4 modelTransform;

public:
	RenderComponent ( Gameobject* pOwner , ModelUPtr model = {} ,ImageUPtr image={} )
	:Component(pOwner){
		_model = std::move ( model );
		_image = std::move ( image);
	
	}
	~RenderComponent ( ) {

	}
	void Update ( );

	void Render ( glm::mat4 projection , glm::mat4 view ) override {
		
		

		_shader->Use ( );
		_shader->SetUniform ( "model" , modelTransform );
		_shader->SetUniform ( "view" , view );
		_shader->SetUniform ( "projection" , projection );
		_shader->SetUniform ( "cameraPos" , GenOwner ( )->GetPos ( ) );
		
		_model->Draw ( _shader.get ( ) );

	}

	
};