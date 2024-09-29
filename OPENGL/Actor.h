#pragma once
#include <iostream>
#include "Component.h"
#include <vector>

class Component;	//부품

using ComponentPtr = std::shared_ptr<Component>;

class Actor {	//부품의 모음 => 객체
public:
	static const uint32_t DEFAULT_COMPONENT_COUNT = 4;
	
	Actor ( ) {
		m_strName = "NONAME";
		m_vecComponent.reserve ( DEFAULT_COMPONENT_COUNT );
	}
	Actor ( const std::string& strName ) :Actor ( ) { m_strName = strName; }

	virtual ~Actor ( ) = default;


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



	template <typename TComponent>
	TComponent* FindComponent ( bool bCheckHiearachy = false )
	{
		// 컴파일 단계에서 막기
		static_assert( std::is_base_of_v<Component , TComponent> , "It's not component!" );

		IComponent* pDestComponent = TComponent::StaticClass ( );
		pDestComponent->InitClassMetadata ( ); // bool 변수로 체크하기 귀찮으니 그냥 계속 초기화

		for ( ComponentPtr spComponent : m_vecComponent )
		{
			RClass* pSrcComponent = spComponent->GetClass ( ); // 캐스팅할 필요는 없음
			Component* pComponentInstance = spComponent.get ( );

			if ( bCheckHiearachy == true )
			{
				if ( pSrcComponent->IsUpperClass ( pDestComponent ) )
				{
					printf ( "Dest는 부모 Component!\n" );
					return static_cast< TComponent* >( pSrcComponent );
				}

				if ( pDestComponent->IsUpperClass ( pSrcComponent ) )
				{
					printf ( "Dest는 자식 Component!\n" );
					printf ( "따라서 static 정보 사용!\n" );
					return TComponent::StaticClass ( );
				}
			}

			if ( pSrcComponent == pDestComponent )
			{
				return static_cast< TComponent* >( pComponentInstance );
			}
		}

		return nullptr;
	}

	void Update ( float deltaTime ) {
		for ( auto& _components : m_vecComponent ) {
			_components->Update ( deltaTime );
		}
	}



	const std::string& GetName ( ) const { return m_strName; }
	void SetName ( const std::string& strName ) { m_strName = strName };

private:
	std::string m_strName;	//총 Component 이름
	
	std::vector<ComponentPtr> m_vecComponent;	//모든 Component 객체들
	

};