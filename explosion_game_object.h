#ifndef EXPLOSION_GAME_OBJECT_H_
#define EXPLOSION_GAME_OBJECT_H_
#include "game_object.h"

namespace game {

    class ExplosionGameObject : public GameObject
    {
    public:
        ExplosionGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float duration = 0.5);
        
        void Update(double delta_time) override;
        bool RegisterHit(void) override;

    protected:
        float time_remaining_;
        
    };
}
#endif

