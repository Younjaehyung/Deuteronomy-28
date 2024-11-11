#include "context.h"
#include "image.h"

ContextUPtr Context::Create ( )
{
    auto context = ContextUPtr ( new Context ( ) ); //context uniquePointer 생성
    if ( !context->Init ( ) ) { //초기화 
        std::cerr << "create Init() err" << std::endl;
        // 실패시
        return nullptr;
    }
    return std::move ( context );   //소유권 이양 (이동연산자)
}

void Context::Render ( ) {

    //imgui 설정 부분
    if ( ImGui::Begin ( "ui window" ) ) {
        //배경색변경 UI 세팅
        if ( ImGui::ColorEdit4 ( "clear color" , glm::value_ptr ( m_clearColor ) ) ) {
            glClearColor ( m_clearColor.r , m_clearColor.g , m_clearColor.b , m_clearColor.a );
        }
        ImGui::Separator ( );   //분할 선 그리기
        ImGui::DragFloat3 ( "camera pos" , glm::value_ptr ( m_cameraPos ) , 0.01f );    //카메라 좌표변경 UI 세팅
        ImGui::DragFloat ( "camera yaw" , &m_cameraYaw , 0.5f );
        ImGui::DragFloat ( "camera pitch" , &m_cameraPitch , 0.5f , -89.0f , 89.0f );
        ImGui::Separator ( );
        if ( ImGui::Button ( "reset camera" ) ) {   //카메라 좌표 리셋 UI 세팅
            m_cameraYaw = 0.0f;
            m_cameraPitch = 0.0f;
            m_cameraPos = glm::vec3 ( 0.0f , 0.0f , 3.0f );
        }
             // 접을 수 있는 헤더, 열려있게 옵션 설정
        if ( ImGui::CollapsingHeader ( "light" , ImGuiTreeNodeFlags_DefaultOpen ) ) {
            ImGui::DragFloat3 ( "l.position" , glm::value_ptr ( m_light.position ) , 0.01f );
            ImGui::DragFloat3 ( "l.direction" , glm::value_ptr ( m_light.direction ) , 0.01f );
            ImGui::DragFloat2 ( "l.cutoff" , glm::value_ptr ( m_light.cutoff ) , 0.1f , 0.0f , 180.0f );
            ImGui::DragFloat  ( "l.distance" , &m_light.distance , 0.1f , 0.0f , 1000.0f );
            ImGui::ColorEdit3 ( "l.ambient" , glm::value_ptr ( m_light.ambient ) );
            ImGui::ColorEdit3 ( "l.diffuse" , glm::value_ptr ( m_light.diffuse ) );
            ImGui::ColorEdit3 ( "l.specular" , glm::value_ptr ( m_light.specular ) );
        }

        if ( ImGui::CollapsingHeader ( "material" , ImGuiTreeNodeFlags_DefaultOpen ) ) {
            ImGui::DragFloat ( "m.shininess" , &m_material->shininess , 1.0f , 1.0f , 256.0f );
        }

         
            ImGui::Checkbox ( "animation" , &m_animation );
        
    }
    ImGui::End ( );

    m_framebuffer->Bind ( );    //사용자정의프레임버퍼 BIND

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅
    glEnable ( GL_DEPTH_TEST ); // DEPTH Buffer 사용 설정

    
    //world 좌표츅 출력///////////////////
    //world_coord_render ( projection , view );
    
    ////cubebox
    //auto skyboxModelTransform =
    //    glm::translate ( glm::mat4 ( 1.0 ) , m_cameraPos ) *
    //    glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 50.0f ) );
    //m_skyboxProgram->Use ( );
    //m_cubeTexture->Bind ( );
    //m_skyboxProgram->SetUniform ( "skybox" , 0 );
    //m_skyboxProgram->SetUniform ( "transform" , projection * view * skyboxModelTransform );
    //m_box->Draw ( m_skyboxProgram.get ( ) );

    //envmap
    auto modelTransform =
        glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.0f , 0.75f , -2.0f ) ) *
        glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 40.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) ) *
        glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
    m_envMapProgram->Use ( );
    m_envMapProgram->SetUniform ( "model" , modelTransform );
    m_envMapProgram->SetUniform ( "view" , view );
    m_envMapProgram->SetUniform ( "projection" , projection );
    m_envMapProgram->SetUniform ( "cameraPos" , m_cameraPos );
    m_cubeTexture->Bind ( );
    m_envMapProgram->SetUniform ( "skybox" , 0 );
    m_box->Draw ( m_envMapProgram.get ( ) );

    //광원/////////////////////////////////////////////
   
    // after computing projection and view matrix
    auto lightModelTransform =
        glm::translate ( glm::mat4 ( 1.0 ) , m_light.position ) *
        glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 0.1f ) );
    m_simpleProgram->Use ( );

    m_simpleProgram->SetUniform ( "color" , glm::vec4 ( m_light.ambient + m_light.diffuse , 1.0f ) );
    m_simpleProgram->SetUniform ( "transform" , projection * view * lightModelTransform );
    m_box->Draw ( m_simpleProgram.get());
    ///////////////////////////////////////////////////


    m_program->Use ( );
    m_program->SetUniform ( "viewPos" , m_cameraPos );
    m_program->SetUniform ( "light.position" , m_light.position );
    m_program->SetUniform ( "light.direction" , m_light.direction );
    m_program->SetUniform ( "light.cutoff" , glm::vec2 (
        cosf ( glm::radians ( m_light.cutoff[ 0 ] ) ) ,
        cosf ( glm::radians ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) ) ) );
    m_program->SetUniform ( "light.attenuation" , GetAttenuationCoeff ( m_light.distance ) );
    m_program->SetUniform ( "light.ambient" , m_light.ambient );
    m_program->SetUniform ( "light.diffuse" , m_light.diffuse );
    m_program->SetUniform ( "light.specular" , m_light.specular );

    
    modelTransform = glm::mat4 ( 1.0f );
    auto transform = projection * view * modelTransform;
    m_program->SetUniform ( "transform" , transform );
    m_program->SetUniform ( "modelTransform" , modelTransform );
    //m_material->SetToProgram ( m_program.get ( ) );
    m_model->Draw ( m_program.get ( ) );

    Framebuffer::BindToDefault ( );
    
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    m_textureProgram->Use ( );
    m_textureProgram->SetUniform ( "transform" ,
        glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    m_framebuffer->GetColorAttachment ( )->Bind ( );
    m_textureProgram->SetUniform ( "tex" , 0 );
    m_plane->Draw ( m_textureProgram.get ( ) );

    Game->Render ( );
}

void Context::ProcessInput ( GLFWwindow* window ) {
    if ( !m_cameraControl )
        return;


    const float cameraSpeed = 0.05f;
    if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * m_cameraFront;
    if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * m_cameraFront;

    auto cameraRight = glm::normalize ( glm::cross ( m_cameraUp , -m_cameraFront ) );
    if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * cameraRight;
    if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * cameraRight;

    auto cameraUp = glm::normalize ( glm::cross ( -m_cameraFront , cameraRight ) );
    if ( glfwGetKey ( window , GLFW_KEY_E ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * cameraUp;
    if ( glfwGetKey ( window , GLFW_KEY_Q ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * cameraUp;
    
}

void Context::Update ( )
{
    Game->Update ( );
    Time::Update ( );
}

void Context::Reshape ( int width , int height ) {
    m_width = width;
    m_height = height;
    glViewport ( 0 , 0 , m_width , m_height );

    //사용자 정의 프레임버퍼 생성
    m_framebuffer = Framebuffer::Create (Texture::Create ( width , height , GL_RGBA ) );
    
}

void Context::MouseMove ( double x , double y ) {
    if ( !m_cameraControl )
        return;
    auto pos = glm::vec2 ( ( float ) x , ( float ) y );
    auto deltaPos = pos - m_prevMousePos;

    const float cameraRotSpeed = 0.8f;
    m_cameraYaw -= deltaPos.x * cameraRotSpeed;
    m_cameraPitch -= deltaPos.y * cameraRotSpeed;

    if ( m_cameraYaw < 0.0f )   m_cameraYaw += 360.0f;
    if ( m_cameraYaw > 360.0f ) m_cameraYaw -= 360.0f;

    if ( m_cameraPitch > 89.0f )  m_cameraPitch = 89.0f;
    if ( m_cameraPitch < -89.0f ) m_cameraPitch = -89.0f;

    
    m_prevMousePos = pos;
}

void Context::MouseButton ( int button , int action , double x , double y ) {
    if ( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        if ( action == GLFW_PRESS ) {
            // 마우스 조작 시작 시점에 현재 마우스 커서 위치 저장
            m_prevMousePos = glm::vec2 ( ( float ) x , ( float ) y );
            m_cameraControl = true;
        }
        else if ( action == GLFW_RELEASE ) {
            m_cameraControl = false;
        }
    }
}


bool Context::Init ( )
{
    world_coord_init ( );

   
    m_box = Mesh::CreateBox ( );
    m_plane = Mesh::CreatePlane ( );

    m_model = Model::Load ( "./model/submarine/Submarine.obj" );

    if ( !m_model ) {
        std::cerr << "program UserSetError id : " << m_model->Get ( ) << std::endl;
        return false;


    }

    
    auto cubeRight = Image::Load ( "./model/skybox/right.jpg" , false );
    auto cubeLeft = Image::Load ( "./model/skybox/left.jpg" , false );
    auto cubeTop = Image::Load ( "./model/skybox/top.jpg" , false );
    auto cubeBottom = Image::Load ( "./model/skybox/bottom.jpg" , false );
    auto cubeFront = Image::Load ( "./model/skybox/front.jpg" , false );
    auto cubeBack = Image::Load ( "./model/skybox/back.jpg" , false );
    m_cubeTexture = CubeTexture::CreateFromImages ( {
        //오른손 좌표계와 {}을 이용해 벡터값을 넣음
      cubeRight.get ( ),
      cubeLeft.get ( ),
      cubeTop.get ( ),
      cubeBottom.get ( ),
      cubeFront.get ( ),
      cubeBack.get ( ),
    } );
    m_skyboxProgram = Program::Create ( "./shader/skybox.vs" , "./shader/skybox.fs" );
    m_envMapProgram = Program::Create ("./shader/env_map.vs" , "./shader/env_map.fs" );

    m_simpleProgram = Program::Create ( "./shader/simple.vs" , "./shader/simple.fs" );
    if ( !m_simpleProgram ) {
        std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
        return false;


    }

    m_program = Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" );
    if ( !m_program ) {
        std::cerr << "program UserSetError id : " << m_program->Get ( ) << std::endl;
        return false;


    }

    m_textureProgram = Program::Create ( "./shader/texture.vs" , "./shader/texture.fs" );
    if ( !m_textureProgram ) {
        std::cerr << "program UserSetError id : " << m_textureProgram->Get ( ) << std::endl;
        return false;


    }
 

    m_material = Material::Create ( );

    m_material->diffuse = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ).get ( ) );

    m_material->specular = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 0.5f , 0.5f , 0.5f , 1.0f ) ).get ( ) );


   
     
    glDisable ( GL_STENCIL_TEST );
   

    glClearColor ( 0.1f , 0.2f , 0.3f , 0.0f );
    std::cerr << "GameManager Init Start" << std::endl;
    Time::Initailize ( );
    Game = new GameManager;
    if ( Game != nullptr ) {
        Game->Initialize ( );
        std::cerr << "GameManager Init" << std::endl;
        return true;
    }
    else {
        
        std::cerr << "GameManager Init Error" << std::endl;
        return false;
    }

    

  return true;
}
