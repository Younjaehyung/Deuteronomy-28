#include "object.h"


class Collision
{
public:
	Collision (Object* object ) {
		collider = object;

	}

	void Update ( );
	void Observer ( );
	void Render ( );
	void SetBox ( glm::vec3 size ) {
		boxsize = size;
	};


	void Initialize ( );


private:
	Object* collider;
	glm::vec3 boxsize;

};

