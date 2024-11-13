#include "GameManager.h"

void OnMouseButton ( GLFWwindow* window , int button , int action , int modifier );
void OnFramebufferSizeChange ( GLFWwindow* window , int width , int height );
void key_pressed ( GLFWwindow* window , int key , int scancode , int action , int mods );
void show_glfw_error ( int error , const char* description );
void OnCursorPos ( GLFWwindow* window , double x , double y );
void OnCharEvent ( GLFWwindow* window , unsigned int ch );
void OnScroll ( GLFWwindow* window , double xoffset , double yoffset );

int main ( )
{
    glfwSetErrorCallback ( show_glfw_error );
    //glfw 초기화
    if ( !glfwInit ( ) ) {
        std::cerr << "GLFW 초기화 실패" << '\n';
        return -1;
    }

    //버전 세팅
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR , 3 );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR , 3 );
    glfwWindowHint ( GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE );
  

    //GLFW 윈도우창 생성
    GLFWwindow* window = glfwCreateWindow ( 640 , 480 , "OpenGL Example" , NULL , NULL );
    if ( !window ) {
        std::cerr << "윈도우 생성 실패" << '\n';
  
        glfwTerminate ( );
        return -1;
    }

    //랜더링 스레드로설정할 openGL 설정
    glfwMakeContextCurrent ( window );

  
   //glew 초기화
    glewExperimental = GL_TRUE;
    GLenum err = glewInit ( );
    if ( err != GLEW_OK ) {
        std::cerr << "GLEW 초기화 실패: " << glewGetErrorString ( err ) << '\n';
        glfwTerminate ( );
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString ( GL_VERSION ) << '\n';

    //// glad를 활용한 OpenGL 함수 로딩
    // glew 내부적으로 처리됨
    //if ( !gladLoadGLLoader ( ( GLADloadproc ) glfwGetProcAddress ) ) {
    //    std::cerr << "failed to initialize glad" << '\n';
    //    glfwTerminate ( );
    //    return -1;
    //}


    //imgui 초기화
    auto imguiContext = ImGui::CreateContext ( );
    ImGui::SetCurrentContext ( imguiContext );
    ImGui_ImplGlfw_InitForOpenGL ( window , false );
    ImGui_ImplOpenGL3_Init ( );
    ImGui_ImplOpenGL3_CreateFontsTexture ( );
    ImGui_ImplOpenGL3_CreateDeviceObjects ( );


    //context 객체 생성
    auto context = Context::Create ( );
    if ( !context ) {
        std::cerr << "failed to create context" << std::endl;


        glfwTerminate ( );
        return -1;
    }
    std::cerr << "윈도우 생성" << '\n';
    
    //glfw userpointer 저장
    glfwSetWindowUserPointer ( window , context.get ( ) );
    //윈도우창 사이즈 설정
    OnFramebufferSizeChange ( window , 640 , 480 );
    glfwSetFramebufferSizeCallback ( window , OnFramebufferSizeChange );
   
    //키보드, 마우스 콜백함수 설정
    glfwSetKeyCallback ( window , key_pressed );
    glfwSetCursorPosCallback ( window , OnCursorPos );
    glfwSetMouseButtonCallback ( window , OnMouseButton );
    glfwSetMouseButtonCallback ( window , OnMouseButton );
    glfwSetCharCallback ( window , OnCharEvent );
;
    while ( !glfwWindowShouldClose ( window ) ) {   //윈도우가 종료되었는지 확인
           glfwPollEvents ( ); //프레임 안정화
           ImGui_ImplGlfw_NewFrame ( );    //imgui 새 랜더링 프레임이라고 알려줌
           ImGui::NewFrame ( );

           context->ProcessInput ( window );    //입력 
           context->Update ( );
           context-> Render ( );    //출력

            
           ImGui::Render ( );    //imgui 정보 종합
           ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData ( ) ); //imgui 그려줌

           glfwSwapBuffers ( window ); //이중버퍼링
      
    }

    //context 객체 소멸
    context.reset ( );
  
    //imgui 종료
    ImGui_ImplOpenGL3_DestroyFontsTexture ( );
    ImGui_ImplOpenGL3_DestroyDeviceObjects ( );
    ImGui_ImplOpenGL3_Shutdown ( );
    ImGui_ImplGlfw_Shutdown ( );
    ImGui::DestroyContext ( imguiContext );

    //glfw 종료
    glfwDestroyWindow ( window );
    glfwTerminate ( );
    return 0;
}



void show_glfw_error ( int error , const char* description ) {
    std::cerr << "Error: " << description << '\n';
}

void OnFramebufferSizeChange ( GLFWwindow* window , int width , int height ) {
    std::cerr << "framebuffer size changed: " << width  << height << std::endl;
    auto context = ( Context* ) glfwGetWindowUserPointer ( window );
    context->Reshape ( width , height );
}

void key_pressed ( GLFWwindow* window , int key , int scancode , int action , int mods ) {
    if ( key == GLFW_KEY_Q && action == GLFW_PRESS ) {
        glfwSetWindowShouldClose ( window , GLFW_TRUE );
    }

    //imgui 키보드 콜백 설정
    ImGui_ImplGlfw_KeyCallback ( window , key , scancode , action , mods );
}

void OnCursorPos ( GLFWwindow* window , double x , double y ) {
    auto context = ( Context* ) glfwGetWindowUserPointer ( window );
    //context->MouseMove ( x , y );
    CameraManager::getInstance ( ).Input ( x , y );
}

void OnMouseButton ( GLFWwindow* window , int button , int action , int modifier ) {
    auto context = ( Context* ) glfwGetWindowUserPointer ( window );
    double x , y;
    glfwGetCursorPos ( window , &x , &y );
    context->MouseButton ( button , action , x , y );
    
    //imgui 마우스 콜백 설정
    ImGui_ImplGlfw_MouseButtonCallback ( window , button , action , modifier );
}

void OnCharEvent ( GLFWwindow* window , unsigned int ch ) {
    ImGui_ImplGlfw_CharCallback ( window , ch );
}

void OnScroll ( GLFWwindow* window , double xoffset , double yoffset ) {
    ImGui_ImplGlfw_ScrollCallback ( window , xoffset , yoffset );
}