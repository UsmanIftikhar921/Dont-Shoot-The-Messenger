#include "collidable.h"	

namespace game {
	class Powerup : public Collidable {
	public:
		Powerup(glm::vec3 position, Geometry* geom, Shader* shader);
	};
}