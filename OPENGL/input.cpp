#include "input.h"

std::vector<input::Key>input::mKeys = {};
//static멤버변수 이므로 전역에서 초기화함.

int ASCII[(uint8_t)eKeyCode::End] = {
	
	GLFW_KEY_Q, GLFW_KEY_W, GLFW_KEY_E, GLFW_KEY_R, GLFW_KEY_T, GLFW_KEY_Y, GLFW_KEY_U, GLFW_KEY_I, GLFW_KEY_O, GLFW_KEY_P,
GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_F, GLFW_KEY_G, GLFW_KEY_H, GLFW_KEY_J, GLFW_KEY_K, GLFW_KEY_L,
GLFW_KEY_Z, GLFW_KEY_X, GLFW_KEY_C, GLFW_KEY_V, GLFW_KEY_B, GLFW_KEY_N, GLFW_KEY_M,
GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5, GLFW_KEY_6,

};

void input::Initialize() {

	for (size_t i = 0; i < ( uint8_t )eKeyCode::End; i++) {

		Key key = {};
		key.bPressed = false;
		key.state = eKeyState::None;
		key.keyCode = (eKeyCode)i;

		mKeys.push_back(key);
	}
}

void input::Update( GLFWwindow* window ) {
	for (size_t i = 0; i < mKeys.size(); i++) {
		//눌렀는지
		if ( glfwGetKey (window,ASCII[i]) == GLFW_PRESS ) {
			if (mKeys[i].bPressed == true) {
				mKeys[i].state = eKeyState::Pressed;
			}
			else {
				mKeys[i].state = eKeyState::Down;
			}
			mKeys[i].bPressed = true;
		}
		else {// 아닌지

			if (mKeys[i].bPressed == true) {
				mKeys[i].state = eKeyState::Up;
			}
			else {
				mKeys[i].state = eKeyState::None;
			}
			mKeys[i].bPressed = false;
		}
		
		
	}
}
