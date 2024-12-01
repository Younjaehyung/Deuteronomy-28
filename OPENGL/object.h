#pragma once
#include "model.h"


enum class eLayerType : uint32_t {
	Player ,
	Enemy ,
	Light ,
	Environment ,
	Item,
	Max // 총 레이어 수
};

struct CollisionObject {
	std::string name;
	glm::vec3 Size = glm::vec3 ( 5.0f , 6.0f , 5.0f );
	
};



class Object {



public:
	int Destroy = 0;	//유효성 0: 실존 1: 없음 (0일시 삭제됨)
	std::string name;	//객체 이름(구체적인)
	int typeID = 0;	//객체 그림자 여부
	eLayerType objectID = eLayerType::Environment;	//객체 속성(충돌처리용)
	glm::vec3 Pos{ 0.0f,0.0f,0.0f };
	glm::mat4 Dir{ glm::mat4(1.0f) };
	
	//std::vector<CollisionObject*> CollisionBox;
	//virtual std::vector<CollisionObject*> GetBox ( ) { return CollisionBox; }
	CollisionObject CollisionBox;
	virtual void Update ( ) {}
	
	virtual CollisionObject GetBox ( ) { return CollisionBox; }	//충돌 박스 리턴
	virtual void SetBox (glm::vec3  size, std::string name="" ) {	//충돌 박스 설정
		CollisionBox.Size = size;
		CollisionBox.name = name;
	}
	
	virtual eLayerType GetObjectID ( ) { return objectID; }	//객체 충돌ID 리턴
	virtual void SetPos ( glm::vec3 pos ) { Pos = pos; }
	virtual glm::vec3& SetPos () { return Pos; }
	virtual glm::vec3 GetPos ( ) {	return Pos;}	
	virtual int& GetDestroy ( ) { return Destroy; }	//삭제할지 리턴



	
	
	//virtual ~Object ( ) {}

	virtual bool HandleCollision ( Object* ) { return true; }	//상호 충돌 확인
	virtual void RenderShadow ( glm::mat4 lightView , const Program* program ) {}	//그림자 랜더링
	virtual void CollisionObserver (std::string& group, Object* object ) {}
};

