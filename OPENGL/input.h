#pragma once
#include "common_include.h"

//숫자를 문자로 변환해주는 클래스임
enum class eKeyState {
	Down,//0
	Pressed,//1
	Up,//2
	None,//3
};

enum class eKeyCode {
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,SPACE,
	End,
};

class input
{
	


public:
	struct Key {
		eKeyCode keyCode;
		eKeyState state;
		bool bPressed;
	};
	static void Initialize();
	static void Update( GLFWwindow* window );

	static bool GetKeyDown(eKeyCode code) {
		return mKeys[( uint32_t )code].state == eKeyState::Down;
	}
	static bool GetKey(eKeyCode code) {
		return mKeys[( uint32_t )code].state == eKeyState::Pressed;
	}
	static bool GetKeyUp(eKeyCode code) {
		return mKeys[( uint32_t )code].state == eKeyState::Up;
	}
	
private:
	static std::vector<Key> mKeys; //공통된 class를 가진 객체들이 공유
};

