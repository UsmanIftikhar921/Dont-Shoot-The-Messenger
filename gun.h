#ifndef GUN_H_
#define GUN_H_

#include "game_object.h"
#include "bullet.h"

namespace game {
	enum FireState {
		COOLDOWN,
		READY,
		FIRING
	};
    class Gun : public GameObject {

    public:
        Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
		~Gun();

        // Update function for moving the player object around
        void Update(double delta_time) override;

		bool TryFire();

		
	protected:
        void Fire();
		float fire_rate_;
		float cooldown_;
		FireState fire_state_;

	};
}

#endif