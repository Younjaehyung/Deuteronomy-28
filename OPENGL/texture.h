#pragma once
#include "image.h"

CLASS_PTR ( Texture )
class Texture {
public:
    static TextureUPtr Create ( int width , int height , uint32_t format );
    static TextureUPtr CreateFromImage ( const Image* image );
    ~Texture ( );

    const uint32_t Get ( ) const { return m_texture; }
    void Bind ( ) const;
    void SetFilter ( uint32_t minFilter , uint32_t magFilter ) const;
    void SetWrap ( uint32_t sWrap , uint32_t tWrap ) const;

    int GetWidth ( ) const { return m_width; }
    int GetHeight ( ) const { return m_height; }
    uint32_t GetFormat ( ) const { return m_format; }
private:
    Texture ( ) {}
    void CreateTexture ( ); //텍스쳐 ID 생성
    void SetTextureFromImage ( const Image* image );    //텍스쳐 설정
    void SetTextureFormat ( int width , int height , uint32_t format ); //빈 텍스쳐 설정


    uint32_t m_texture{ 0 };
    int m_width{ 0 };
    int m_height{ 0 };
    uint32_t m_format{ GL_RGBA };
};

CLASS_PTR ( CubeTexture )
class CubeTexture {
public:
    static CubeTextureUPtr CreateFromImages (const std::vector<Image*>& images );
    ~CubeTexture ( );

    const uint32_t Get ( ) const { return m_texture; }
    void Bind ( ) const;
private:
    CubeTexture ( ) {}
    bool InitFromImages ( const std::vector<Image*>& images );      //이미지들을 받아서 큐브를 생성함
    uint32_t m_texture{ 0 };
};