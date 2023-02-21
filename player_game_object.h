#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "collidable_game_object.h"

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public CollidableGameObject {

        public:
            PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float collision_radius);

            // Update function for moving the player object around
            void Update(double delta_time) override;

        private:
    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
