#pragma once
#include "common_include.h"

CLASS_PTR ( Image )
class Image {
public:
    
    static ImageUPtr Load ( const std::string& filepath , bool flipVertical = true );
    static ImageUPtr Create ( int width , int height , int channelCount = 4 );  //이미지 저장소 색성
    static ImageUPtr CreateSingleColorImage (int width , int height , const glm::vec4& color );    //단색 테스쳐 생성
    static ImageUPtr LoadFromMemory ( const unsigned char* data , int size , bool flipVertical);
    ~Image ( );

    const uint8_t* GetData ( ) const { return m_data; }
    int GetWidth ( ) const { return m_width; }
    int GetHeight ( ) const { return m_height; }
    int GetChannelCount ( ) const { return m_channelCount; }


private:
    Image ( ) {};
    bool LoadWithStbFromMemory ( const unsigned char* data , int size , bool flipVertical );
    bool LoadWithStb ( const std::string& filepath , bool flipVertical );   //이미지 로딩
    bool Allocate ( int width , int height , int channelCount );
    int m_width{ 0 };
    int m_height{ 0 };
    int m_channelCount{ 0 };
    uint8_t* m_data{ nullptr };
};

