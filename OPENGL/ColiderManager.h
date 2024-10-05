#pragma once
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"


class ColiderManager {

public:

	static void Update ( );
	static void Initialize ( );
	static void FixedUpdate ( );
	static void Render ( );
	static void CollisionLayerCheck ( );
	static void LayerCollistion ( );
	static void ColliderCollision ( );
	static bool Intersect ( );


private:
	static void 

};