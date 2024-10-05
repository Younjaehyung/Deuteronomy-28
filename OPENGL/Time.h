#pragma once
#include <chrono>
#include <iostream>

class Time{
public:
    static void Initialize ( );  // Time 초기화용
    static void Update ( );      // deltatime 갱신용
    static void Render ( );      // 화면 프레임 체크용

private:
    static std::chrono::high_resolution_clock::time_point PrevTime;
    static std::chrono::high_resolution_clock::time_point CurrentTime;
    static float DeltaTimeValue;
};
