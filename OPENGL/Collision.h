#include "object.h"
#include "Player.h"


class Collision
{
public:
	void Update ( );
	void SetCollision ( Object* collider_box );
	void Observer ( );
	void Render ( );
	void SetBox ( Object* object );
	void Initialize ( );


private:
	std::vector<Object*> collider;
	Object* player;
	Object* monster;

	struct Line {
		float x;
		float y;
	};
};

