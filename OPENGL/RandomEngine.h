#pragma once
#include <algorithm>
#include <random>
class RandomEngine
{
public:
	static std::mt19937& GetEngine ( );
};

