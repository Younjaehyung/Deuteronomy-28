#pragma once
#include "model.h"


enum class eLayerType : uint32_t {
	Player ,
	Enemy ,
	Light ,
	Environment ,
	Max // 총 레이어 수
};

struct CollisionObject {
	std::string name;
	glm::vec3 Size = glm::vec3 ( 5.0f , 6.0f , 5.0f );
	
};



class Object {



public:

	std::string name;
	int typeID = 0;
	eLayerType objectID = eLayerType::Environment;
	glm::vec3 Pos{ 0.0f,0.0f,0.0f };
	glm::mat4 Dir{ glm::mat4(1.0f) };
	
	//std::vector<CollisionObject*> CollisionBox;
	//virtual std::vector<CollisionObject*> GetBox ( ) { return CollisionBox; }
	CollisionObject CollisionBox;
	virtual void Update ( ) {}
	
	virtual CollisionObject GetBox ( ) { return CollisionBox; }
	
	virtual eLayerType GetObjectID ( ) { return objectID; }
	virtual void SetPos ( glm::vec3 pos ) { Pos = pos; }
	virtual glm::vec3& SetPos () { return Pos; }
	virtual glm::vec3 GetPos ( ) {	return Pos;}


	virtual void AddBox ( std::string& name ,glm::vec3 size ) { 
		CollisionObject* box = new CollisionObject;
		box->name = name;
		box->Size = size;
		//CollisionBox.push_back( box );
	 }
	//virtual void RemoveBox ( std::string& name) {}

	
	


	virtual void HandleCollision (Object* ) {}
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) {}
	virtual void CollisionObserver (std::string& group, Object* object ) {}
};

