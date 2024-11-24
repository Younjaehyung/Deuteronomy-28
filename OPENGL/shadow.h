#pragma once
#include "texture.h"

CLASS_PTR ( ShadowMap );
class ShadowMap {
public:
	static ShadowMapUPtr Create ( int width , int height );
	~ShadowMap ( );

	const uint32_t Get ( ) const { return m_framebuffer; }
	void Bind ( ) const;
	const TexturePtr GetShadowMap ( ) const { return m_shadowMap; }

private:
	ShadowMap ( ) {}
	bool Init ( int width , int height );

	uint32_t m_framebuffer{ 0 };
	TexturePtr m_shadowMap;	//쉐도우 맵
};

//쉐도우맵이기에 z값만 필요하지 컬러나 다른 값들은 필요하지 않는다.