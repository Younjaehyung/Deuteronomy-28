#include "buffer.h"


BufferUPtr Buffer::CreateWithData (uint32_t bufferType , uint32_t usage ,const void* data , size_t stride , size_t count ){

    auto buffer = BufferUPtr ( new Buffer ( ) );
    if ( !buffer->Init ( bufferType , usage , data , stride , count ) )
        return nullptr;
    return std::move ( buffer );
}


Buffer::~Buffer ( ) {
    if ( m_buffer ) {
        glDeleteBuffers ( 1 , &m_buffer );
    }
}

void Buffer::Bind ( ) const {
    glBindBuffer ( m_bufferType , m_buffer );
}

bool Buffer::Init(uint32_t bufferType , uint32_t usage , const void* data , size_t stride , size_t count ) {

    m_bufferType = bufferType;
    m_usage = usage;
    m_stride = stride;
    m_count = count;
    glGenBuffers ( 1 , &m_buffer );
    Bind ( );
    glBufferData ( m_bufferType , stride*count , data , usage );
    //glBufferData()에 메모리 포인터 인자에 nullptr을 넘겨주면, 메모리 할당만 하고 복사는 일어나지 않음
    return true;
}

//glGenBuffers ( 1 , &m_vertexBuffer );   //vertex 버퍼 생성
//glBindBuffer ( GL_ARRAY_BUFFER , m_vertexBuffer );  //지금부터 사용할 buffer object을 바인딩해줌    
//                                                    //GL_ARRAY_BUFFER : 사용할 buffer object는 vertex data를 저장할 용도임을 알려줌
//glBufferData ( GL_ARRAY_BUFFER , sizeof ( float ) *12 , vertices ,  GL_STATIC_DRAW );   //buffer에 data 복사
