#include "context.h"
#include "image.h"
#include "Time.h"
#include "Sound.h"
#include "CollisionManager.h"
#include "input.h"
//ContextUPtr Context::Create ( )
//{
//    auto context = ContextUPtr ( new Context ( ) ); //context uniquePointer 생성
//    if ( !context->Initialize ( ) ) { //초기화 
//        std::cerr << "create Init() err" << std::endl;
//        // 실패시
//        return nullptr;
//    }
//    return std::move ( context );   //소유권 이양 (이동연산자)
//}

void Context::Render ( ) {

    std::cout << "PlayMode" << std::endl;
    //IMGUI_USER ( );
    std::cout << "PlayMode" << std::endl;
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

   



    LightManager::getInstance ( ).UpdateShadowMaps ( obj );
    glViewport ( 0 , 0 , m_width , m_height );
    if ( player->GetSeekState() ) {
        m_framebuffer->Bind ( );    //사용자정의프레임버퍼 BIND
        
        glViewport ( 0 , 0 , m_width/5 *2 , m_height );
       
        //CollisionManager::getInstance ( ).Render ( );   //맵 그리드

        glDisable ( GL_CULL_FACE );

        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅

        //손전등
        //m_assimp_Program->Use ( );
        MainDraw ( CameraManager::getInstance ( ).GetCameraPos ( ) , CameraManager::getInstance ( ).Camera_transform ( ) );

        
        glViewport ( m_width / 5 *2 , 0 , m_width / 5 * 3 , m_height );
        MainDraw ( CameraManager::getInstance ( ).GetCamera2Pos ( ) , CameraManager::getInstance ( ).Camera2_transform ( ) );
        SplitUIDraw ( );
        Framebuffer::BindToDefault ( );

        m_textureProgram->Use ( );
        m_textureProgram->SetUniform ( "typeID" , 0 );

        m_framebuffer->GetColorAttachment ( )->Bind ( );
        m_textureProgram->SetUniform ( "tex" , 0 );

        glViewport (0, 0 , m_width  , m_height );
        m_plane->Draw ( m_textureProgram.get ( ) );
    }
    else {
        glViewport ( 0 , 0 , m_width , m_height );
        

        m_framebuffer->Bind ( );    //사용자정의프레임버퍼 BIND
        //CollisionManager::getInstance ( ).Render ( );   //맵 그리드

        glDisable ( GL_CULL_FACE );

        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //GL_DEPTH_BUFFER_BIT : DEPTH Buffer clear 세팅

        //손전등
        //m_assimp_Program->Use ( );
        MainDraw ( CameraManager::getInstance ( ).GetCameraPos ( ) , CameraManager::getInstance ( ).Camera_transform ( ) );



        if ( player->IsFlashLight ( ) ) {

            UIDraw ( );
        }
        if (  object1->GetPhase ( ) ) {
           // PhaseDraw ( );
        }
        Framebuffer::BindToDefault ( );


        m_textureProgram->Use ( );
        if ( player->IsFlashLight ( ) ) {
            m_textureProgram->SetUniform ( "typeID" , 1 );

            if ( 1 == object1->GetPhase ( ) ) {
                m_textureProgram->SetUniform ( "typeID" , 2 );
            }
            else if ( 2 == object1->GetPhase ( ) ) {
                m_textureProgram->SetUniform ( "typeID" , -1 );
            }
            else if ( 3 == object1->GetPhase ( ) ) {
                m_textureProgram->SetUniform ( "typeID" , -1 );
            }
        }
        else {
            m_textureProgram->SetUniform ( "typeID" , 0 );
        }
       

        ////이중버퍼링

        m_textureProgram->SetUniform ( "transform" ,
            glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
        m_framebuffer->GetColorAttachment ( )->Bind ( );
        m_textureProgram->SetUniform ( "tex" , 0 );

        m_textureProgram->SetUniform ( "resolution" , glm::vec2 ( 2560 , 1440 ) );
        nowTime += Time::DeltaTime ( );
        m_textureProgram->SetUniform ( "time" , nowTime );

        m_plane->Draw ( m_textureProgram.get ( ) );
        
    }
    


}

void Context :: Update ( ) {
   
    GameobjectDelete ( );   //삭제

    CameraManager::getInstance ( ).Update ( );  //업데이트
    Camera_Transform = CameraManager::getInstance ( ).Camera_transform( );
    GameobjectUpdate ( );
    Door1->GetItemCount (player->GetItem() );
    Door2->GetItemCount ( player->GetItem ( ) );

    if ( player->GetItem ( )==5 && Ending ==0) {
        Ending = 1;
        Object* Corridor7 = new Object;
        Corridor7->name = "exit";
        Corridor7->SetPos ( glm::vec3 ( 116.0f , 0.0f , -96.0f ) );
        Corridor7->SetBox ( glm::vec3 ( 4.0f ) , "Escape" );
        Corridor7->SetobjectID ( eLayerType::Item );
        obj.push_back ( Corridor7 );
        object1->notifyFromMap ( player->GetPos() , 1 );
    }

    CollisionManager::getInstance ( ).Update (obj );    //충돌체



}

void Context::ProcessInput ( GLFWwindow* window ) {
    
    player->Input ( window );


    if ( input::GetKeyDown ( eKeyCode::F ) ) {
        CameraLight = player->IsFlashLight ( );
    }

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
    //std::cout << m_height << std::endl;
    //사용자 정의 프레임버퍼 생성
    m_framebuffer = Framebuffer::Create (Texture::Create ( m_width , m_height , GL_RGBA ) );
    
}

void Context::MainDraw (glm::vec3 _pos, glm::mat4 _cameraTransform )
{
    m_lightingShadowProgram->Use ( );
    glm::vec3 CameraPos ( _pos );
    m_lightingShadowProgram->SetUniform ( "viewPos" , _pos );
    m_lightingShadowProgram->SetUniform ( "blinn" , ( m_blinn ? 1 : 0 ) );
    LightManager::getInstance ( ).UpdateShadowMapping ( m_lightingShadowProgram.get ( ) );

    for ( auto& _object : obj ) {
        if ( _object->typeID == 0 ) {
            _object->Render ( m_lightingShadowProgram.get ( ) , _cameraTransform );
        }
    }
   
    
   
    
    m_animationProgram->Use ( );
    m_animationProgram->SetUniform ( "viewPos" , _pos );
    m_animationProgram->SetUniform ( "modelTransform" , glm::mat4 ( 1.0f ) );
    m_animationProgram->SetUniform ( "transform" , _cameraTransform );
    m_animationProgram->SetUniform ( "blinn" , ( m_blinn ? 1 : 0 ) );
    LightManager::getInstance ( ).UpdateShadowMapping ( m_animationProgram.get ( ) );

    for ( auto& _object : obj ) {
        if ( _object->typeID == 1 ) {
            _object->Render ( m_animationProgram.get ( ) , _cameraTransform );
        }
    }


}

void Context::FrameBufferDraw ( )
{
}

void Context::UIDraw ( )
{
    glDisable ( GL_DEPTH_TEST ); 

    m_camerauiProgram->Use ( );
    m_camerauiProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    CameraUITEXTURE->Bind ( );
    m_camerauiProgram->SetUniform ( "tex" , 0 );

    // 블렌딩 활성화
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    // 캠코더 UI 렌더링
    m_plane->Draw ( m_camerauiProgram.get ( ) );

    if ( RecTime <= 3.0f ) {
        RecTime += Time::DeltaTime ( ) * 3.0f;
        RecUITEXTURE->Bind ( );
    }
    else if ( RecTime > 3.0f  && RecTime <= 6.0f) {
        RecTime += Time::DeltaTime ( ) * 3.0f;
    }
    else {
        RecTime = 0.0f;
    }


    m_camerauiProgram->SetUniform ( "tex" , 0 );
    m_plane->Draw ( m_camerauiProgram.get ( ) );
    // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
    glDisable ( GL_BLEND );

    glEnable ( GL_DEPTH_TEST );
}

void Context::PhaseDraw ( )
{
    glDisable ( GL_DEPTH_TEST );

    m_camerauiProgram->Use ( );
    m_camerauiProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    
    if ( 1 == object1->GetPhase ( ) ) {
        Phase1UITEXTURE->Bind ( );

    }
    else if (  2== object1->GetPhase ( ) ) {
        Phase2UITEXTURE->Bind ( );
    }
    else if ( 3 == object1->GetPhase ( ) ) {
        Phase2UITEXTURE->Bind ( );
    }
   
    m_camerauiProgram->SetUniform ( "tex" , 0 );

    // 블렌딩 활성화
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    // 캠코더 UI 렌더링
    m_plane->Draw ( m_camerauiProgram.get ( ) );


    m_camerauiProgram->SetUniform ( "tex" , 0 );
    m_plane->Draw ( m_camerauiProgram.get ( ) );
    // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
    glDisable ( GL_BLEND );

    glEnable ( GL_DEPTH_TEST );
}

void Context::SplitUIDraw ( )
{
    glViewport ( 0 , 0 , m_width , m_height );


    glDisable ( GL_DEPTH_TEST );

    m_camerauiProgram->Use ( );
    m_camerauiProgram->SetUniform ( "transform" , glm::scale ( glm::mat4 ( 1.0f ) , glm::vec3 ( 2.0f , 2.0f , 1.0f ) ) );
    SplitUITEXTURE->Bind ( );
    m_camerauiProgram->SetUniform ( "tex" , 0 );

    // 블렌딩 활성화
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    // 캠코더 UI 렌더링
    m_plane->Draw ( m_camerauiProgram.get ( ) );

    // 블렌딩 비활성화 (다른 렌더링에 영향 없도록)
    glDisable ( GL_BLEND );

    glEnable ( GL_DEPTH_TEST );
}



void Context::MouseButton ( int button , int action , double x , double y ) {
    /*if ( button == GLFW_MOUSE_BUTTON_RIGHT ) {
        if ( action == GLFW_PRESS ) {
             //마우스 조작 시작 시점에 현재 마우스 커서 위치 저장
            m_prevMousePos = glm::vec2 ( ( float ) x , ( float ) y );
            
            CameraManager::getInstance().ClickCamera ( ) = true;
        }
        else if ( action == GLFW_RELEASE ) {
           
            CameraManager::getInstance ().ClickCamera ( )  = false;
        }
    }*/
    //추가
    //CameraManager::getInstance ( ).ClickCamera ( ) = true;
}


bool Context::Initialize ( )
{

    m_box = Mesh::CreateBox ( );
    m_plane = Mesh::CreatePlane ( );
    auto CameraUi = Image::Load ( "./model/UI/Camera.png" , false );
    CameraUITEXTURE = Texture::CreateFromImage ( CameraUi.get());
    CameraUi = Image::Load ( "./model/UI/CameraRec.png" , false );
    RecUITEXTURE = Texture::CreateFromImage ( CameraUi.get ( ) );

    if ( CUTEMDOE == 0 ) {
        auto SplitUi = Image::Load ( "./model/UI/SplitUI.png" , false );
        SplitUITEXTURE = Texture::CreateFromImage ( SplitUi.get ( ) );
    }
    else {
        auto SplitUi = Image::Load ( "./model/UI/Cute_SplitUI.png" , false );
        SplitUITEXTURE = Texture::CreateFromImage ( SplitUi.get ( ) );
    }


    auto Phase1 = Image::Load ( "./model/UI/Phase1.png" , false );
    Phase1UITEXTURE = Texture::CreateFromImage ( Phase1.get ( ) );
    auto Phase2 = Image::Load ( "./model/UI/Phase2.png" , false );
    Phase2UITEXTURE = Texture::CreateFromImage ( Phase2.get ( ) );

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

    m_simpleAnimationProgram = Program::Create ( "./shader/simple_animation.vs" , "./shader/simple_animation.fs" );
    if ( !m_simpleAnimationProgram ) {
        std::cerr << "program UserSetError id : " << m_simpleAnimationProgram->Get ( ) << std::endl;
        return false;


    }

    m_camerauiProgram = Program::Create ( "./shader/cameraUI.vs" , "./shader/cameraUI.fs" );
    if ( !m_camerauiProgram ) {
        std::cerr << "program UserSetError id : " << m_camerauiProgram->Get ( ) << std::endl;
        return false;


    }


    m_material = Material::Create ( );
    
    m_material->diffuse = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ).get ( ) );

    m_material->specular = Texture::CreateFromImage ( Image::CreateSingleColorImage ( 4 , 4 ,
        glm::vec4 ( 0.5f , 0.5f , 0.5f , 1.0f ) ).get ( ) );


    LightManager::getInstance ( ).Initialize ( m_simpleProgram.get ( ) , m_simpleAnimationProgram.get ( ) );


    mainCamera = new Camera;
    player = new Player;

    item0 = new Item ( glm::vec3 ( 66.0f , 0.0f , -54.0f ) );
    item1 = new Item ( glm::vec3 ( 41.0f , 0.0f , -7.5f ) );
    item2 = new Item ( glm::vec3 ( 112.0f , 0.0f , -66.0f ) );
    item3 = new Item ( glm::vec3 ( 69.0f , 0.0f , -115.0f ) );
    item4 = new Item ( glm::vec3 ( -15.0f , 0.0f , -54.0f ) );
    Door1 = new Door ( glm::vec3 ( -3.0f , 0.0f , -52.0f ) );
    Door2 = new Door ( glm::vec3 ( 116.0f , 0.0f , -96.0f ) );
    object1 = new character( glm::vec3(84.0f , 0.0f , -10.0f) );
    //object2 = new character( glm::vec3 (94.0f , 0.0f , -60.0f ) );
    map = new Map();

   
    map->Initialize ("./model/NewNewNew.glb" );

    object1->Initialize ( "./model/HULK1/HulkIdle.glb" );

    //->Initialize ( "./model/BagMan2.glb" );
    item0->Initialize ( "./model/Cross.glb" );
    item1->Initialize ( "./model/Cross.glb" );
    item2->Initialize ( "./model/Cross.glb" );
    item3->Initialize ( "./model/Cross.glb" );
    item4->Initialize ( "./model/Cross.glb" );
    Door1->Initialize ( "./model/Door.glb" );
    Door2->Initialize ( "./model/Door.glb" );
    player->Initialize ("./model/SibalGLB/SibalIdle.glb" );
    CollisionManager::getInstance ( ).Initialize ( );
    CameraManager::getInstance ( ).SetCamera ( player->camera );
    CameraManager::getInstance ( ).SetCamera2 ( mainCamera );

    
   light1 = new LightMass;
   light1->SetLight ( glm::vec3 ( 2.0f , 4.0f , -1.0f ) , glm::vec3 ( 3.0f , 0.0f , 0.0f ) , glm::vec2 ( 60.0f , 5.0f ) );
   LightManager::getInstance ( ).AddLight ( light1 );

   player->SetPos (glm::vec3(  -32.0f , 0.0f , -6.0f) );

    obj.push_back ( object1 );
   // obj.push_back ( object2 );
    obj.push_back ( item0 );
    obj.push_back ( item1 );
    obj.push_back ( item2 );
    obj.push_back ( item3 );
    obj.push_back ( item4 );
    obj.push_back ( Door1 );
    obj.push_back ( Door2 );
    obj.push_back ( map );
    obj.push_back ( player );
    map->ObjectInitialize ( obj, object1 );
    glDisable ( GL_STENCIL_TEST );
    glClearColor ( 0.0f , 0.0f , 0.0f , 1.0f );
    //CameraManager::getInstance ( ).ClickCamera ( ) = true;
  return true;
}



bool Context::Reset ( )
{
    GameobjectDeleteAll ( );



    mainCamera = new Camera;
    player = new Player;

    item0 = new Item ( glm::vec3 ( 66.0f , 0.0f , -54.0f ) );
    item1 = new Item ( glm::vec3 ( 41.0f , 0.0f , -7.5f ) );
    item2 = new Item ( glm::vec3 ( 112.0f , 0.0f , -66.0f ) );
    item3 = new Item ( glm::vec3 ( 69.0f , 0.0f , -115.0f ) );
    item4 = new Item ( glm::vec3 ( -15.0f , 0.0f , -54.0f ) );
    Door1 = new Door ( glm::vec3 ( -3.0f , 0.0f , -52.0f ) );
    Door2 = new Door ( glm::vec3 ( 116.0f , 0.0f , -94.0f ) );
    object1 = new character ( glm::vec3 ( 84.0f , 0.0f , -10.0f ) );
    //object2 = new character ( glm::vec3 ( 94.0f , 0.0f , -60.0f ) );
 


    map->Initialize ( "./model/NewNewNew.glb" );

    object1->Initialize ( "./model/HULK1/HulkIdle.glb" );

    //object2->Initialize ( "./model/BagMan2.glb" );
    item0->Initialize ( "./model/Cross.glb" );
    item1->Initialize ( "./model/Cross.glb" );
    item2->Initialize ( "./model/Cross.glb" );
    item3->Initialize ( "./model/Cross.glb" );
    item4->Initialize ( "./model/Cross.glb" );
    Door1->Initialize ( "./model/Door.glb" );
    Door2->Initialize ( "./model/Door.glb" );
    player->Initialize ( "./model/SibalGLB/SibalIdle.glb" );
    CollisionManager::getInstance ( ).Initialize ( );
    CameraManager::getInstance ( ).SetCamera ( player->camera );
    CameraManager::getInstance ( ).SetCamera2 ( mainCamera );


    light1 = new LightMass;
    light1->SetLight ( glm::vec3 ( 2.0f , 4.0f , -1.0f ) , glm::vec3 ( 3.0f , 0.0f , 0.0f ) , glm::vec2 ( 60.0f , 5.0f ) );
    LightManager::getInstance ( ).AddLight ( light1 );

    player->SetPos ( glm::vec3 ( -32.0f , 0.0f , -6.0f ) );

    obj.push_back ( object1 );
    // obj.push_back ( object2 );
    obj.push_back ( item0 );
    obj.push_back ( item1 );
    obj.push_back ( item2 );
    obj.push_back ( item3 );
    obj.push_back ( item4 );
    obj.push_back ( Door1 );
    obj.push_back ( Door2 );
    obj.push_back ( map );
    obj.push_back ( player );
    map->ObjectInitialize ( obj , object1 );


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
        ImGui::DragFloat3 ( "main camera pos" , glm::value_ptr ( player->SetPos ( ) ) , 0.01f );    //카메라 좌표변경 UI 세팅
        ImGui::DragFloat ( "main camera yaw" , &m_cameraYaw , 0.5f );
        ImGui::DragFloat ( "main camera pitch" , &m_cameraPitch , 0.5f , -89.0f , 89.0f );

        ImGui::Separator ( );   //분할 선 그리기
        ImGui::DragFloat3 ( "camera pos" , glm::value_ptr ( m_cameraP ) , 0.01f );    //카메라 좌표변경 UI 세팅
        ImGui::DragFloat3 ( "camera dir" , glm::value_ptr ( m_cameraD ) , 0.01f );
        ImGui::DragFloat3 ( "camera up" , glm::value_ptr ( m_cameraU ) , 0.01f );


        mainCamera->SetCamera ( m_cameraP , m_cameraD , m_cameraU );

        ImGui::Separator ( );
        if ( ImGui::Button ( "reset camera" ) ) {   //카메라 좌표 리셋 UI 세팅
            m_cameraYaw = 0.0f;
            m_cameraPitch = 0.0f;
            m_cameraPos = glm::vec3 ( 0.0f , 0.0f , 3.0f );
        }
        // 접을 수 있는 헤더, 열려있게 옵션 설정
        if ( ImGui::CollapsingHeader ( "light" , ImGuiTreeNodeFlags_DefaultOpen ) ) {
            ImGui::DragFloat3 ( "l.position" , glm::value_ptr ( light1->SetlightData ( )->position ) , 0.01f );
            ImGui::DragFloat3 ( "l.direction" , glm::value_ptr ( light1->SetlightData ( )->direction ) , 0.01f );
            ImGui::DragFloat2 ( "l.cutoff" , glm::value_ptr ( m_light.cutoff ) , 0.1f , 0.0f , 180.0f );
            ImGui::DragFloat ( "l.distance" , &m_light.distance , 0.1f , 0.0f , 1000.0f );
            ImGui::ColorEdit3 ( "l.ambient" , glm::value_ptr ( light1->SetlightData ( )->ambient ) );
            ImGui::ColorEdit3 ( "l.diffuse" , glm::value_ptr ( light1->SetlightData ( )->diffuse ) );
            ImGui::ColorEdit3 ( "l.specular" , glm::value_ptr ( light1->SetlightData ( )->specular ) );

            light1->SetlightData ( )->attenuation = GetAttenuationCoeff ( m_light.distance );
            light1->SetlightView ( ) = glm::lookAt ( light1->SetlightData ( )->position , light1->SetlightData ( )->position + light1->SetlightData ( )->direction , glm::vec3 ( 0.0f , 1.0f , 0.0f ) );

            light1->SetlightData ( )->cutoff = glm::vec2 (
            cosf ( glm::radians ( m_light.cutoff[ 0 ] ) ) , cosf ( glm::radians ( m_light.cutoff[ 0 ] + m_light.cutoff[ 1 ] ) ) );

        }

        if ( ImGui::CollapsingHeader ( "material" , ImGuiTreeNodeFlags_DefaultOpen ) ) {
            ImGui::DragFloat ( "m.shininess" , &m_material->shininess , 1.0f , 1.0f , 256.0f );
        }

        ImGui::Checkbox ( "l.blinn" , &m_blinn );
        ImGui::Checkbox ( "animation" , &m_animation );
        
        float aspectRatio = ( float ) m_width / ( float ) m_width;
        ImGui::Image ( ( ImTextureID ) m_framebuffer->GetColorAttachment ( )->Get ( ) , ImVec2 ( 150 * aspectRatio , 150 ) );
        
        ImGui::Image ( ( ImTextureID ) LightManager::getInstance ( ).GetShadowMap ( 1 )->GetShadowMap ( )->Get ( ) , ImVec2 ( 256 , 256 ) , ImVec2 ( 0 , 1 ) , ImVec2 ( 1 , 0 ) );
    }
    ImGui::End ( );
    
}


