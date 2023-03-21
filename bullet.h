#ifndef BULLET_H_
#define BULLET_H_

#include "collidable.h"

namespace game {

    // Inherits from GameObject
    class Bullet : public Collidable {

        public:
            Bullet(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update function for moving the bullet object around
            void Update(double delta_time) override;

            bool RayCircleCollision(glm::vec2 rayOrigin, glm::vec2 rayVector, glm::vec2 circleCenter, float radius, float &t1, float &t2);
            int CheckForCollision(std::vector<GameObject*> obj);

            void HandleCollisionEvent(CollisionEvent& event) override;

        private:
            glm::vec2 start_; 
            float time_since_fire_ = 0.0f;
            float last_time_since_fire_ = 0.0f;

    }; // class Bullet

} // namespace game

#endif // BULLET_H_