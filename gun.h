#ifndef GUN_H_
#define GUN_H_

#include "game_object.h"
#include "task.h"
#include "bullet.h"
#include "big_bullet.h"

#include <random>
#include <glm/gtc/matrix_transform.hpp> 


namespace game {

    enum GunType {
        STANDARD,
        HEAVY,
    };
    
    class Gun : public Task {

    public:
        Gun(const glm::vec3& position, Geometry* geom, Shader* shader, bool frieindly, GunType type = STANDARD);
        Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, bool friendly, GunType type = STANDARD);
		~Gun();

        // Update function for moving the player object around
        void Update(double delta_time) override;

		bool PerformTask(float efficiency_modifier) override;

		
	protected:
        void Fire();
        GunType gun_type_;
        bool friendly_;
	};
}

#endif