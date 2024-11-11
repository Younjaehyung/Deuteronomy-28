#pragma once

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

//glad


//3차원 좌표계 변환 관련 glm
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

//imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <optional>




#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

std::optional<std::string> LoadTextFile ( const std::string& filename );

glm::vec3 GetAttenuationCoeff ( float distance );	//Point Light 감쇠 계산 함수

//매크로 Shader 클래스
#define CLASS_PTR(klassName)\
class klassName;\
using klassName##UPtr = std::unique_ptr<klassName>;\
using klassName##Ptr = std::shared_ptr<klassName>;\
using klassName##WPtr = std::weak_ptr<klassName>;

////자체 함수
//const char* getGLErrorString ( GLenum error ) {
//    switch ( error ) {
//    case GL_NO_ERROR: return "No error";
//    case GL_INVALID_ENUM: return "Invalid enum";
//    case GL_INVALID_VALUE: return "Invalid value";
//    case GL_INVALID_OPERATION: return "Invalid operation";
//    case GL_STACK_OVERFLOW: return "Stack overflow";
//    case GL_STACK_UNDERFLOW: return "Stack underflow";
//    case GL_OUT_OF_MEMORY: return "Out of memory";
//    case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
//    default: return "Unknown error";
//    }
//}
//
//void checkGLError ( ) {
//    GLenum error;
//    while ( ( error = glGetError ( ) ) != GL_NO_ERROR ) {
//        std::cerr << "OpenGL Error: " << getGLErrorString ( error ) << std::endl;
//        // 추가 오류 처리
//    }
//}

