#ifndef PLAYER_H_
#define PLAYER_H_

#include "collidable.h"
#include "bullet.h"

namespace game {

    // Inherits from GameObject
    class Player : public Collidable {

        public:
            Player(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update function for moving the player object around
            void Update(double delta_time, GuiState* gui_state) override;

            void HandleCollisionEvent(CollisionEvent& event) override;

            bool canShoot();
            void initBullet(Bullet** bullet, glm::vec3 position, glm::vec3 velocity, float rotation);

        private:
            float time_since_last_shot_ = 0.0f;
            const float time_between_shots_ = 0.5f;
    }; // class Player

} // namespace game

#endif // PLAYER_H_
