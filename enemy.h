#ifndef ENEMY_H_
#define ENEMY_H_

#include "collidable.h"

namespace game {

    /* Chaser Enemy: */
    class ChaserEnemy : public Collidable {

    public:
        ChaserEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        void Update(double delta_time) override;

        void HandleCollisionEvent(CollisionEvent& event) override;

        void SetTarget(glm::vec3 target) { target_ = target; }

        void ChaseTarget(double delta_time);

        glm::vec2 GetMousePos();

        void SetWindow(GLFWwindow* window) { window_ = window; }

        //bool canShoot();
        //void initBullet(Bullet** bullet, glm::vec3 position, glm::vec3 velocity, float rotation);

    private:
        GLFWwindow* window_;
        glm::vec3 target_;
        float max_speed_ = 2.0f;
        float acceleration_ = 0.4f;
        //float time_since_last_shot_ = 0.0f;
        //const float time_between_shots_ = 0.5f;
    }; // class Enemy

} // namespace game

#endif // ENEMY_H_
