#ifndef PLAYER_H_
#define PLAYER_H_

#include "collidable.h"

namespace game {

    // Inherits from GameObject
    class Player : public Collidable {

        public:
            Player(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update function for moving the player object around
            void Update(double delta_time) override;

            void HandleCollisionEvent(CollisionEvent& event) override;

        private:
    }; // class Player

} // namespace game

#endif // PLAYER_H_
