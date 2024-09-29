#pragma once

class Actor;

class Component {
public:
	Component ( Actor* pOwner ) { m_pOwner = pOwner; }
	virtual ~Component ( ) = default;

	virtual void Update ( float deltaTime ) = 0;

	//리턴값
	Actor* GenOwner ( ) { return m_pOwner; }	
	const Actor* GetOwner ( ) const { return m_pOwner; }
private:
	Actor* m_pOwner = nullptr;	//Actor 자료형.
};

class PhysicsComponent : public Component {
public:
	void Update ( float deltaTime ) override {
		// 물리 처리
	}
};

class RenderComponent : public Component {
public:
	void Update ( float deltaTime ) override {
		

	}
};