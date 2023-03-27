#ifndef GUN_H_
#define GUN_H_

#include "game_object.h"
#include "bullet.h"

namespace game {

    // Inherits from GameObject
    class Gun : public GameObject {

    public:
        Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        // Update function for moving the player object around
        void Update(double delta_time) override;

        //void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, double current_time) override;

        void Fire();

    private:
        float cooldown_timer_ = 0.0f;
        const float fire_rate_ = 0.5f;
        bool can_fire_ = true;

    }; // class Gun

} // namespace game

#endif // GUN_H_