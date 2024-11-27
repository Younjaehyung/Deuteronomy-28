#include "context.h"
#include "image.h"
#include "Time.h"
#include "Sound.h"
#include "CollisionManager.h"
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

    
    IMGUI_USER ( );
    glEnable ( GL_DEPTH_TEST ); // DEPTH Buffer 사용 설정
  
    //cubebox
    //auto skyboxModelTransform =
    //    glm::translate ( glm::mat4 ( 1.0 ) , m_cameraPos ) *
    //    glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 50.0f ) );
    //m_skyboxProgram->Use ( );
    //m_cubeTexture->Bind ( );
    //m_skyboxProgram->SetUniform ( "skybox" , 0 );
    //m_skyboxProgram->SetUniform ( "transform" , Camera_Transform * skyboxModelTransform );
    //m_box->Draw ( m_skyboxProgram.get ( ) );

    //envmap
    /*auto modelTransform =
        glm::translate ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.0f , 0.75f , -2.0f ) ) *
        glm::rotate ( glm::mat4 ( 1.0f ) , glm::radians ( 40.0f ) , glm::vec3 ( 0.0f , 1.0f , 0.0f ) ) *
        glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 1.5f , 1.5f , 1.5f ) );
    m_envMapProgram->Use ( );
    m_envMapProgram->SetUniform ( "model" , modelTransform );
    m_envMapProgram->SetUniform ( "camera" , Camera_Transform );
    m_envMapProgram->SetUniform ( "cameraPos" , m_cameraPos );
    m_cubeTexture->Bind ( );
    m_envMapProgram->SetUniform ( "skybox" , 0 );
    m_box->Draw ( m_envMapProgram.get ( ) );*/

    //광원/////////////////////////////////////////////
   
    // after computing projection and view matrix
    //auto lightModelTransform =// m_light.position
    //    glm::translate ( glm::mat4 ( 1.0 ) ,glm::vec3(0.0f,0.0f,0.0f) ) *
    //    glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 1.0f ) );
    //m_simpleProgram->Use ( );

    //m_simpleProgram->SetUniform ( "color" , glm::vec4 ( m_light.ambient + m_light.diffuse , 1.0f ) );
    //m_simpleProgram->SetUniform ( "transform" , Camera_Transform * lightModelTransform );
    //m_box->Draw ( m_simpleProgram.get());
    ///////////////////////////////////////////////////

    //m_shadowMap->Bind ( );
    //glClear ( GL_DEPTH_BUFFER_BIT );
    //glEnable(GL_CULL_FACE);
    //glCullFace ( GL_FRONT_FACE );

    //glViewport ( 0 , 0 ,
    //    m_shadowMap->GetShadowMap ( )->GetWidth ( ) ,
    //    m_shadowMap->GetShadowMap ( )->GetHeight ( ) );
   
    //m_simpleProgram->Use ( );


    //auto lightView = glm::lookAt ( glm::vec3 ( -1.0f , 2.0f , 0.0f ) ,
    //glm::vec3 ( -1.0f , 2.0f , 0.0f ) + glm::vec3 ( 2.5f , -1.5f , -1.0f ) ,
    //glm::vec3 ( 0.0f , 1.0f , 0.0f ) );
    //auto lightProjection = glm::perspective (
    //  glm::radians ( ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) * 2.0f ) ,
    //  1.0f , 1.0f , 20.0f );//lightProjection* lightView 
    //m_simpleProgram->SetUniform ( "color" , glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
    //m_simpleProgram->SetUniform ( "transform" , CameraManager::getInstance ( ).Camera_transform ( ) );
    //m_simpleProgram->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f ) );
    //DrawScene (  m_simpleProgram.get ( ) );

    //Framebuffer::BindToDefault ( );



    LightManager::getInstance ( ).UpdateShadowMaps ( obj );

    glViewport ( 0 , 0 , m_width , m_height );

    //m_framebuffer->Bind ( );    //사용자정의프레임버퍼 BIND
    glDisable ( GL_CULL_FACE );

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅
    //CollisionManager::getInstance ( ).Render ( );   //맵 그리드

    //손전등
    //m_assimp_Program->Use ( );
    m_lightingShadowProgram->Use ( );
    
    glm::vec3 CameraPos ( CameraManager::getInstance ( ).GetCameraPos ( ) );
    m_lightingShadowProgram->SetUniform ( "viewPos" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    //m_lightingShadowProgram->SetUniform ( "light.position" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    //m_lightingShadowProgram->SetUniform ( "light.direction" , CameraManager::getInstance ( ).GetCameraFront());
    //m_lightingShadowProgram->SetUniform ( "light.cutoff" , glm::vec2 (
       // cosf ( glm::radians ( m_light.cutoff[ 0 ] ) ) ,
      //  cosf ( glm::radians ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) ) ) );
    //m_lightingShadowProgram->SetUniform ( "light.attenuation" , GetAttenuationCoeff ( m_light.distance ) );
    //m_lightingShadowProgram->SetUniform ( "light.ambient" , m_light.ambient );
    //m_lightingShadowProgram->SetUniform ( "light.diffuse" , m_light.diffuse );
    //m_lightingShadowProgram->SetUniform ( "light.specular" , m_light.specular );
    m_lightingShadowProgram->SetUniform ( "blinn" , ( m_blinn ? 1 : 0 ) );
    //m_lightingShadowProgram->SetUniform ( "light.directional" ,m_light.directional ? 1 : 0 );
    //m_lightingShadowProgram->SetUniform ( "lightTransform" , CameraManager::getInstance().Camera_transform () );
    m_lightingShadowProgram->SetUniform ( "modelTransform" , glm::mat4(1.0f) );
    m_lightingShadowProgram->SetUniform ( "transform" , Camera_Transform );
    m_lightingShadowProgram->SetUniform ( "numLights" , LightManager::getInstance ( ).GetLightNum ( ) );
    m_lightingShadowProgram->SetUniform ( "lightTransform[0]" , LightManager::getInstance ( ).GetLightTransform ( 0 ) );
    glActiveTexture ( GL_TEXTURE0 +3 );
    LightManager::getInstance ( ).GetShadowMap ( 0 )->GetShadowMap ( )->Bind ( );
    m_lightingShadowProgram->SetUniform ( "shadowMaps[0]" , 3 );
    //glm::mat4  lightTransform;
    //for ( int i = 0; i < LightManager::getInstance ( ).GetLightNum ( ); i++ ) {
    //    std::string base = "lightTransform[" + std::to_string ( i ) + "]";

    //    lightTransform = LightManager::getInstance().GetLightTransform(i); // 라이트의 lightSpaceMatrix 계산

    //    glUniform4fv ( glGetUniformLocation ( m_lightingShadowProgram->Get() , ( base).c_str ( ) ) , 1 , glm::value_ptr ( lightTransform ) );

    //    


    //    glActiveTexture ( GL_TEXTURE0 +5+i);
    //    base = "shadowMaps[" + std::to_string ( i ) + "]";
    //    LightManager::getInstance ( ).GetShadowMap ( i )->GetShadowMap ( )->Bind ( );
    //  // m_lightingShadowProgram->SetUniform ( "shadowMap[" + std::to_string ( i ) + "]" , 3+i );  // 각 라이트의 그림자 맵 바인딩
    //   glUniform1i ( glGetUniformLocation ( m_lightingShadowProgram->Get ( ) , ( base ).c_str ( ) ) ,  5+i );

    //   std::cout << glGetUniformLocation ( m_lightingShadowProgram->Get ( ) , ( base ).c_str ( ) ) << std::endl;

    //}
   
    glActiveTexture ( GL_TEXTURE0 );

    map->Render ( m_lightingShadowProgram.get ( ) );

    //auto lightModelTransform =// m_light.position
    //    glm::translate ( glm::mat4 ( 1.0 ) , glm::vec3 ( 0.0f , 0.0f , 0.0f ) ) *
    //    glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 1.0f ) );
    //m_simpleProgram->Use ( );

    //m_simpleProgram->SetUniform ( "color" , glm::vec4 ( m_light.ambient + m_light.diffuse , 1.0f ) );
    //m_simpleProgram->SetUniform ( "transform" , Camera_Transform * lightTransform * glm::scale ( glm::mat4 ( 1.0 ) , glm::vec3 ( 10.0f ) ));
    //m_box->Draw ( m_simpleProgram.get ( ) );

    //m_material->SetToProgram ( m_program.get ( ) );
    //m_animationProgram
    
    //m_animationProgram->Use ( );
    //손전등
    //m_animationProgram->SetUniform ( "viewPos" , CameraManager::getInstance().GetCameraPos() );
    //m_animationProgram->SetUniform ( "light.position" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    //m_animationProgram->SetUniform ( "light.direction" , CameraManager::getInstance ( ).GetCameraFront() );
    //m_animationProgram->SetUniform ( "light.cutoff" , glm::vec2 (
    //    cosf ( glm::radians ( m_light.cutoff[ 0 ] ) ) ,
    //    cosf ( glm::radians ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) ) ) );
    //m_animationProgram->SetUniform ( "light.attenuation" , GetAttenuationCoeff ( m_light.distance ) );
    //m_animationProgram->SetUniform ( "light.ambient" , m_light.ambient );
    //m_animationProgram->SetUniform ( "light.diffuse" , m_light.diffuse );
    //m_animationProgram->SetUniform ( "light.specular" , m_light.specular );

    //glm::vec3 CameraPos ( CameraManager::getInstance ( ).GetCameraPos ( ) );
    //m_animationProgram->SetUniform ( "viewPos" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    //m_animationProgram->SetUniform ( "numLights" , LightManager::getInstance ( ).GetLightNum ( ) );
    //m_animationProgram->SetUniform ( "blinn" , ( m_blinn ? 1 : 0 ) );
    //m_animationProgram->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f ) );
    ////m_animationProgram->SetUniform ( "transform" , Camera_Transform );
    //for ( int i = 0; i < LightManager::getInstance ( ).GetLightNum(); i++ ) {
    //    glm::mat4 lightTransform = LightManager::getInstance ( ).GetLightTransform ( i ); // 라이트의 lightSpaceMatrix 계산
    //    m_lightingShadowProgram->SetUniform ( "lightTransform[" + std::to_string ( i ) + "]" , lightTransform );
    //    std::cout<< "lightTransform[" + std::to_string ( i ) + "]" <<std::endl;
    //    glActiveTexture ( GL_TEXTURE0 + i );
    //    LightManager::getInstance ( ).GetShadowMap ( i )->Bind ( );
    //    m_lightingShadowProgram->SetUniform ( "shadowMap[" + std::to_string ( i ) + "]" , i );  // 각 라이트의 그림자 맵 바인딩
    //}


    //object1->Render_2pass ( m_animationProgram.get ( ) );
    //player->Render ( m_animationProgram.get ( ) );

   


    //Framebuffer::BindToDefault ( );
    //
    //glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );


    ////이중버퍼링
    //m_textureProgram->Use ( );
    //m_textureProgram->SetUniform ( "transform" ,
    //    glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    //m_framebuffer->GetColorAttachment ( )->Bind ( );
    //m_textureProgram->SetUniform ( "tex" , 0 );
    //m_textureProgram->SetUniform ( "resolution" , glm::vec2 ( 2560 , 1440 ) );
    //nowTime += Time::DeltaTime ( );
    //m_textureProgram->SetUniform ( "time" , nowTime );

    //m_plane->Draw ( m_textureProgram.get ( ) );
}

void Context :: Update ( ) {
    Time::Update ( );
    CameraManager::getInstance ( ).Update ( );
    Camera_Transform = CameraManager::getInstance ( ).Camera_transform( );
    player->Update ( );
    object1->Update();
}

void Context::ProcessInput ( GLFWwindow* window ) {
    
    player->Input ( window );
   /* glm::vec3 cameraDirectionXZ = glm::normalize ( glm::vec3 ( m_cameraFront.x , 0.0f , m_cameraFront.z ) );
    const float cameraSpeed = 0.05f;
    if ( glfwGetKey ( window , GLFW_KEY_W ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * cameraDirectionXZ;
    if ( glfwGetKey ( window , GLFW_KEY_S ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * cameraDirectionXZ;

    auto cameraRight = glm::normalize ( glm::cross ( -m_cameraUp , cameraDirectionXZ ) );
    if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * cameraRight;
    if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * cameraRight;

    auto cameraUp = glm::normalize ( glm::cross ( -m_cameraFront , cameraRight ) );
    if ( glfwGetKey ( window , GLFW_KEY_D ) == GLFW_PRESS )
        m_cameraPos += cameraSpeed * cameraRight;
    if ( glfwGetKey ( window , GLFW_KEY_A ) == GLFW_PRESS )
        m_cameraPos -= cameraSpeed * cameraRight;*/
}

void Context::Reshape ( int width , int height ) {
    m_width = width;
    m_height = height;
    glViewport ( 0 , 0 , m_width , m_height );
   
    if ( m_width <= 1 ) {
        m_width = 1;
    }
    if ( m_height <= 1 ) {
        m_height = 1;
    }
    std::cout << m_height << std::endl;
    //사용자 정의 프레임버퍼 생성
    m_framebuffer = Framebuffer::Create (Texture::Create ( m_width , m_height , GL_RGBA ) );
    
}

void Context::DrawScene (const Program* program )
{
    //program->Use ( );
    glm::vec3 CameraPos ( CameraManager::getInstance ( ).GetCameraPos ( ) );
    program->SetUniform ( "viewPos" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    program->SetUniform ( "light.position" , CameraManager::getInstance ( ).GetCameraPos ( ) );
    program->SetUniform ( "light.direction" , CameraManager::getInstance ( ).GetCameraFront ( ) );
    program->SetUniform ( "light.cutoff" , glm::vec2 (
        cosf ( glm::radians ( m_light.cutoff[ 0 ] ) ) ,
        cosf ( glm::radians ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) ) ) );
    program->SetUniform ( "light.attenuation" , GetAttenuationCoeff ( m_light.distance ) );
    program->SetUniform ( "light.ambient" , m_light.ambient );
    program->SetUniform ( "light.diffuse" , m_light.diffuse );
    program->SetUniform ( "light.specular" , m_light.specular );
    program->SetUniform ( "light.directional" , m_light.directional ? 1 : 0 );
    program->SetUniform ( "blinn" , m_blinn ? 1 : 0 );
    auto transform = Camera_Transform;


    
    map->Render ( program );


    object1->Render ( program );
    player->Render ( program );
}



void Context::MouseButton ( int button , int action , double x , double y ) {
    if ( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        if ( action == GLFW_PRESS ) {
            // 마우스 조작 시작 시점에 현재 마우스 커서 위치 저장
            m_prevMousePos = glm::vec2 ( ( float ) x , ( float ) y );
            
            CameraManager::getInstance().ClickCamera ( ) = true;
        }
        else if ( action == GLFW_RELEASE ) {
           
            CameraManager::getInstance ().ClickCamera ( )  = false;
        }
    }
}


bool Context::Init ( )
{
    //glEnable (GL_ );
    m_box = Mesh::CreateBox ( );
    m_plane = Mesh::CreatePlane ( );

    //map = Model::Load ( "./model/submarine/Submarine.obj" );

    //if ( !map ) {
    //    std::cerr << "program UserSetError id : " << map->Get ( ) << std::endl;
    //    return false;

     
    //}

    
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
   
    m_animationProgram = Program::Create ( "./shader/animation.vs" , "./shader/animation.fs" );
    if ( !m_animationProgram ) {
        std::cerr << "program UserSetError id : " << m_animationProgram->Get ( ) << std::endl;
        return false;


    }
    
    m_assimp_Program = Program::Create ( "./shader/assimp_light.vs" , "./shader/assimp_light.fs" );
    if ( !m_animationProgram ) {
        std::cerr << "program UserSetError id : " << m_animationProgram->Get ( ) << std::endl;
        return false;


    }
    
    m_lightingShadowProgram = Program::Create ("./shader/lighting_shadow.vs" , "./shader/lighting_shadow.fs" );
    if ( !m_lightingShadowProgram ) {
        std::cerr << "program UserSetError id : " << m_lightingShadowProgram->Get ( ) << std::endl;
        return false;


    }

    m_shadowMap = ShadowMap::Create ( 2048 , 2048 );



    m_material = Material::Create ( );
    
    m_material->diffuse = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ).get ( ) );

    m_material->specular = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 0.5f , 0.5f , 0.5f , 1.0f ) ).get ( ) );


    mainCamera = new Camera;
    player = new Player;
    map = new Map;
    object1 = new character;
    //CollisionManager::getInstance ( ).Initialize ( );
    


    map->Initialize ("./model/11.24NewNew.glb" );
    object1->Initialize ( "./model/monster_m/NiddleHeadRun.glb" );
    player->Initialize ("./model/SibalGLB/SibalIdle.glb" );

    Time::Initailize ( );
    SoundManager::getInstance ( ).Initialize ( );

    CameraManager::getInstance ( ).SetCamera ( player->camera );

    LightManager::getInstance ( ).Initialize ( m_simpleProgram.get ( ) );
    LightManager::getInstance ( ).SetLight ( glm::vec3 ( 2.0f , 4.0f , -1.0f ) , glm::vec3 ( 3.0f , 0.0f , 0.0f ) , glm::vec2 ( 60.0f , 5.0f ) );


    //obj.push_back ( object1 );
    obj.push_back ( map );
    //obj.push_back ( player );

    glDisable ( GL_STENCIL_TEST );
    glClearColor ( 1.0f , 1.0f , 1.0f , 1.0f );

  return true;
}

void Context::IMGUI_USER ( ) {
    //imgui 설정 부분
    if ( ImGui::Begin ( "ui window" ) ) {
        //배경색변경 UI 세팅
        if ( ImGui::ColorEdit4 ( "clear color" , glm::value_ptr ( m_clearColor ) ) ) {
            glClearColor ( m_clearColor.r , m_clearColor.g , m_clearColor.b , m_clearColor.a );
        }
        ImGui::Separator ( );   //분할 선 그리기
        ImGui::DragFloat3 ( "camera pos" , glm::value_ptr ( player->GetPos ( ) ) , 0.01f );    //카메라 좌표변경 UI 세팅
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
            ImGui::DragFloat ( "l.distance" , &m_light.distance , 0.1f , 0.0f , 1000.0f );
            ImGui::ColorEdit3 ( "l.ambient" , glm::value_ptr ( m_light.ambient ) );
            ImGui::ColorEdit3 ( "l.diffuse" , glm::value_ptr ( m_light.diffuse ) );
            ImGui::ColorEdit3 ( "l.specular" , glm::value_ptr ( m_light.specular ) );

           
        }

        if ( ImGui::CollapsingHeader ( "material" , ImGuiTreeNodeFlags_DefaultOpen ) ) {
            ImGui::DragFloat ( "m.shininess" , &m_material->shininess , 1.0f , 1.0f , 256.0f );
        }

        ImGui::Checkbox ( "l.blinn" , &m_blinn );
        ImGui::Checkbox ( "animation" , &m_animation );

        float aspectRatio = ( float ) m_width / ( float ) m_width;
        ImGui::Image ((ImTextureID) m_framebuffer->GetColorAttachment ( )->Get ( ) , ImVec2 ( 150 * aspectRatio , 150 ) );
        
        ImGui::Image ( ( ImTextureID ) LightManager::getInstance ( ).GetShadowMap ( 0 )->GetShadowMap ( )->Get ( ) ,ImVec2 ( 256 , 256 ) , ImVec2 ( 0 , 1 ) , ImVec2 ( 1 , 0 ) );
    }
    ImGui::End ( );

}