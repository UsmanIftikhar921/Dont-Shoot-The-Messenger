#ifndef BIG_BULLET_H_
#define BIG_BULLET_H_

#include "game_object.h"
#include "bullet.h"

namespace game {

    // Inherits from GameObject
    class BigBullet : public Bullet {

    public:
        BigBullet(const glm::vec3& position, Geometry* geom, Shader* shader);

        // Update function for moving the bullet object around
        void Update(double delta_time) override;

        inline float GetSpeed(void) { return speed_; }

    private:
        float speed_;
		float rotation_speed_;

    }; // class Bullet

} // namespace game

#endif // BULLET_H_