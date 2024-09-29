#pragma once

class Gameobject;

class Component {
public:
	Component ( Gameobject* pOwner ) { m_pOwner = pOwner; }
	virtual ~Component ( ) = default;

	virtual void Update ( float deltaTime ) = 0;
	virtual void FixedUpdate ( ) = 0;
	virtual void Render ( ) = 0;


	//리턴값
	Gameobject* GenOwner ( ) { return m_pOwner; }
	const Gameobject* GetOwner ( ) const { return m_pOwner; }

private:
	Gameobject* m_pOwner = nullptr;	//Gameobject 자료형.
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