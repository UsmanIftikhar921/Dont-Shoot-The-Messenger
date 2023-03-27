#ifndef GUN_H_
#define GUN_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class Gun : public GameObject {

    public:


    private:
        float time_since_last_shot_ = 0.0f;
        const float fire_rate_ = 0.5f;

    }; // class Gun

} // namespace game

#endif // GUN_H_