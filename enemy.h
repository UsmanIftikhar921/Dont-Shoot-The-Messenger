#ifndef ENEMY_H_
#define ENEMY_H_

#include "collidable.h"

namespace game {

    // Enum of States
    enum class EnemyState {
		IDLE,
		CHASING,
        ORBITING,
		ATTACKING,
		DYING,
		DEAD
	};

    /* Chaser Enemy: */
    class ChaserEnemy : public Collidable {

    public:
        ChaserEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        void Update(double delta_time) override;

        void HandleCollisionEvent(CollisionEvent& event) override;

        void ChangeState(float delta_time);

        void SetTarget(glm::vec3 target) { target_ = target; }

        void HomeInOnPoint(glm::vec3& target, float delta_time);

        void OrbitAroundTarget(glm::vec3& target, float radius, double delta_time);

        glm::vec2 GetMousePos();

        void SetWindow(GLFWwindow* window) { window_ = window; }

    private:
        GLFWwindow* window_;
        EnemyState state_ = EnemyState::CHASING;
        glm::vec3 target_;
        glm::vec3 acceleration_;

    }; // class Enemy

} // namespace game

#endif // ENEMY_H_
