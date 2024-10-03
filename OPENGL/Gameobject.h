#pragma once
#include <iostream>
#include "Component.h"
#include <vector>
#include "Common.h"
#include "CameraManager.h"
#include "common_include.h"

class Component;	//부품

using ComponentPtr = std::shared_ptr<Component>;

class Gameobject {	//부품의 모음 => 객체
public:
	static const uint32_t DEFAULT_COMPONENT_COUNT = 4;
	
	Gameobject ( ) {
		m_strName = "NONAME";
		m_vecComponent.reserve ( DEFAULT_COMPONENT_COUNT );
	}
	Gameobject ( const std::string& strName ) :Gameobject ( ) { m_strName = strName; }

	virtual ~Gameobject ( ) = default;

	
	template <typename TComponent>
	bool AddComponent ( ) {
		
		if ( FindComponent<TComponent> ( ) != nullptr ) {
			//이미 같은 component가 있으면 추가 하지 않음.
			return false;
		}
		
		//새로운 component를 추가
		//소유자는 자기로 설정
		ComponentPtr spComponent = std::make_shared<TComponent> ( this );

		if ( spComponent == nullptr ) {
			
			return false;
		}
		
		m_vecComponent.push_back ( spComponent );


		return true;
	}


	//component 삭제
	template <typename Tcomponent>
	bool RemoveComponent ( ) {
		Tcomponent* pComponent = FindComponent<Tcomponent> ( );
		if ( pComponent == nullptr ) {
			//해당 component가 없으면 넘김
			return false;
		}

		//remove_if : 해당 값이 맞는 원소들을 begin()부터 end()까지 검색해서 제거함
		auto foundIter = std::remove_if ( m_vecComponent.begin ( ) , m_vecComponent.end ( ) ,
			[pComponent]( ComponentPtr spComponent )
			{
				return ( pComponent == spComponent.get ( ) );
			} );

		m_vecComponent.erase ( foundIter );
		return true;
	}



	//component 검색
	template <typename TComponent>
	TComponent* FindComponent ( bool bCheckHiearachy = false )
	{
		// 컴파일 단계에서 막기
		static_assert( std::is_base_of_v<Component , TComponent> , "It's not component!" );

		for ( ComponentPtr spComponent : m_vecComponent )
		{
			// 현재 컴포넌트가 원하는 타입인지 확인
			TComponent* pComponent = dynamic_cast< TComponent* >( spComponent.get ( ) );

			if ( pComponent != nullptr )
			{
				return pComponent;
			}
		}

		return nullptr;
	}

	void Update ( float deltaTime );

	void FixedUpdate ( );

	void Render ( );
		




	glm::vec3& GetPos ( ) {
		return Pos;
	}

	glm::vec3& GetDir ( ) {
		return Dir;
	}

	void SetPos (glm::vec3 pos ) {
		Pos = pos;
	}

	void SetDir ( glm::vec3 dir ) {
		Dir = dir;
	}

	const std::string& GetName ( ) const { return m_strName; }
	void SetName ( const std::string& strName ) { m_strName = strName; }

private:

	std::string m_strName;	//총 Component 이름
	
	std::vector<ComponentPtr> m_vecComponent;	//모든 Component 객체들
	
	glm::vec3 Pos = glm::vec3 ( 0.0f , 0.0f , 0.0f );	//위치
	glm::vec3 Dir = glm::vec3 ( 0.0f , 0.0f , 1.0f );	//방향
};