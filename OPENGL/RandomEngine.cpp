#include "RandomEngine.h"

std::mt19937& RandomEngine::GetEngine ( )
{
    static std::mt19937 engine ( std::random_device{}( ) );
    return engine;
}
