#ifndef BULLET_H_
#define BULLET_H_

#include "game_object.h"
#include "collidable.h"

namespace game {

    // Inherits from GameObject
    class Bullet : public Collidable {

        public:
            Bullet(const glm::vec3& position, Geometry* geom, Shader* shader, bool friendly);

            // Update function for moving the bullet object around
            void Update(double delta_time, GuiState* gui_state) override;

            inline float GetSpeed(void) { return speed_; }

        private:
            float speed_;

    }; // class Bullet

} // namespace game

#endif // BULLET_H_