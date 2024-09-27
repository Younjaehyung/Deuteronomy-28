#include "framebuffer.h"

FramebufferUPtr Framebuffer::Create ( const TexturePtr colorAttachment ) {
    auto framebuffer = FramebufferUPtr ( new Framebuffer ( ) );
    if ( !framebuffer->InitWithColorAttachment ( colorAttachment ) )
        return nullptr;
    return std::move ( framebuffer );
}

Framebuffer::~Framebuffer ( ) {
    if ( m_depthStencilBuffer ) {
        glDeleteRenderbuffers ( 1 , &m_depthStencilBuffer );
    }
    if ( m_framebuffer ) {
        glDeleteFramebuffers ( 1 , &m_framebuffer );
    }
}

void Framebuffer::BindToDefault ( ) {
    glBindFramebuffer ( GL_FRAMEBUFFER , 0 );
}

void Framebuffer::Bind ( ) const {
    glBindFramebuffer ( GL_FRAMEBUFFER , m_framebuffer );
}

bool Framebuffer::InitWithColorAttachment ( const TexturePtr colorAttachment ) {
    m_colorAttachment = colorAttachment;
    glGenFramebuffers ( 1 , &m_framebuffer );   //사용자 정의 프레임버퍼 생성
    glBindFramebuffer ( GL_FRAMEBUFFER , m_framebuffer );

    glFramebufferTexture2D ( GL_FRAMEBUFFER ,   
      GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D ,
      colorAttachment->Get ( ) , 0 );   //해당 프레임버퍼의 결과값을 담을 텍스쳐 ID 연결

    glGenRenderbuffers ( 1 , &m_depthStencilBuffer );   //랜더버퍼 생성
    glBindRenderbuffer ( GL_RENDERBUFFER , m_depthStencilBuffer );  
    glRenderbufferStorage (
      GL_RENDERBUFFER , GL_DEPTH24_STENCIL8 ,
      colorAttachment->GetWidth ( ) , colorAttachment->GetHeight ( ) ); //랜더버퍼 설정
    glBindRenderbuffer ( GL_RENDERBUFFER , 0 ); //랜더버퍼 체인지

    glFramebufferRenderbuffer (
      GL_FRAMEBUFFER , GL_DEPTH_STENCIL_ATTACHMENT ,
      GL_RENDERBUFFER , m_depthStencilBuffer ); //프레임버퍼 랜더버펑 연결

    auto result = glCheckFramebufferStatus ( GL_FRAMEBUFFER );
    if ( result != GL_FRAMEBUFFER_COMPLETE ) {
        std::cerr<< "failed to create framebuffer" << result <<std::endl;
        return false;
    }

    BindToDefault ( );  //메인프레임버퍼로 변경

    return true;
}