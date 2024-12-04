#pragma once
#include "model.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraManager.h"
#include "object.h"
#include "LightMass.h"



class Scene : public Object{
private:
	
public:
	Scene ( ) {};
	virtual ~Scene ( ) {};

	virtual void Update ( )
	{

	}

	virtual bool Initialize ( )
	{
		return true;
	}

	virtual void ProcessInput ( GLFWwindow* window )
	{
	
	}

	virtual void MouseButton ( int button , int action , double x , double y ) {
	
	}

	virtual void FixedUpdate ( ){

	}

	virtual void Render ( )
	{

	}

	virtual void Reshape ( int width , int height ) {
		std::cout << "나는 정왕의 오승원이다" << std::endl;
	}

	virtual int Check () {
		return true;
	}
};