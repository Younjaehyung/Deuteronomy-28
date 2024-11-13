#include "image.h"
#define STB_IMAGE_IMPLEMENTATION  // STB 관련 파일 define
#include "include/STB/stb_image.h"

// 파일에서 이미지 로드
ImageUPtr Image::Load ( const std::string& filepath , bool flipVertical ) {
    auto image = ImageUPtr ( new Image ( ) );
    if ( !image->LoadWithStb ( filepath , flipVertical ) )
        return nullptr;
    return std::move ( image );
}

// 메모리에서 이미지 로드 (GLB 파일 내장 텍스처용)
ImageUPtr Image::LoadFromMemory ( const unsigned char* data , int size , bool flipVertical ) {
    auto image = ImageUPtr ( new Image ( ) );
    if ( !image->LoadWithStbFromMemory ( data , size , flipVertical ) )
        return nullptr;
    return std::move ( image );
}

// 새 이미지 생성
ImageUPtr Image::Create ( int width , int height , int channelCount ) {
    auto image = ImageUPtr ( new Image ( ) );
    if ( !image->Allocate ( width , height , channelCount ) )
        return nullptr;
    return std::move ( image );
}

// 이미지 메모리 할당
bool Image::Allocate ( int width , int height , int channelCount ) {
    m_width = width;
    m_height = height;
    m_channelCount = channelCount;
    m_data = ( uint8_t* ) malloc ( m_width * m_height * m_channelCount );
    return m_data ? true : false;
}

// 이미지 소멸자
Image::~Image ( ) {
    if ( m_data ) {
        stbi_image_free ( m_data );
    }
}

// STB를 사용하여 파일에서 이미지 로드
bool Image::LoadWithStb ( const std::string& filepath , bool flipVertical ) {
    stbi_set_flip_vertically_on_load ( flipVertical );
    m_data = stbi_load ( filepath.c_str ( ) , &m_width , &m_height , &m_channelCount , 0 );
    if ( !m_data ) {
        std::cerr << "failed to load image: " << filepath << std::endl;
        return false;
    }
    return true;
}

// STB를 사용하여 메모리에서 이미지 로드
bool Image::LoadWithStbFromMemory ( const unsigned char* data , int size , bool flipVertical ) {
    stbi_set_flip_vertically_on_load ( flipVertical );
    m_data = stbi_load_from_memory ( data , size , &m_width , &m_height , &m_channelCount , 0 );
    if ( !m_data ) {
        std::cerr << "failed to load image from memory" << std::endl;
        return false;
    }
    return true;
}

// 단색 이미지 생성
ImageUPtr Image::CreateSingleColorImage ( int width , int height , const glm::vec4& color ) {
    glm::vec4 clamped = glm::clamp ( color * 255.0f , 0.0f , 255.0f );
    uint8_t rgba[ 4 ] = {
        ( uint8_t ) clamped.r,
        ( uint8_t ) clamped.g,
        ( uint8_t ) clamped.b,
        ( uint8_t ) clamped.a,
    };

    auto image = Create ( width , height , 4 );
    for ( int i = 0; i < width * height; i++ ) {
        memcpy ( image->m_data + 4 * i , rgba , 4 );
    }
    return std::move ( image );
}
