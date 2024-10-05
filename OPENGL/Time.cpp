#include "Time.h"

std::chrono::high_resolution_clock::time_point Time::PrevTime;
std::chrono::high_resolution_clock::time_point Time::CurrentTime;
float Time::DeltaTimeValue = 0.0f;

void Time::Initialize ( ) {
    // 프로그램 시작 시 시간 초기화
    PrevTime = std::chrono::high_resolution_clock::now ( );
}

void Time::Update ( ) {
    // 현재 시간을 얻고, deltatime 계산
    CurrentTime = std::chrono::high_resolution_clock::now ( );
    std::chrono::duration<float> deltaTime = CurrentTime - PrevTime;
    DeltaTimeValue = deltaTime.count ( );
    PrevTime = CurrentTime;
}

void Time::Render ( ) {
    // 프레임 체크용 코드
    float fps = 1.0f / DeltaTimeValue;

    if ( fps < 100 ) {   // 100 fps 이하일 경우 출력
        std::wcout << L"FPS: " << static_cast< int >( fps ) << std::endl;
    }
}