#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include "geometry.h"

#include <unordered_map>

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of one object in the game world
        The update and render methods are virtual, so you can inherit them from GameObject and override the update or render functionality (see PlayerGameObject for reference)
    */

    enum ObjType {
        OBJ,
        COLLECTIBLE,
        PLAYER,
        ENEMY,
		EXPLOSION,
    };
    
    class GameObject {

        public:
            // Constructor
            GameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture);
            ~GameObject();

            // Update the GameObject's state. Can be overriden in children
            virtual void Update(double delta_time);

            // Renders the GameObject 
            virtual void Render(glm::mat4 view_matrix, double current_time);

            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline float GetScale(void) { return scale_; }
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline ObjType GetType(void) { return type_; }

            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetScale(float scale) { scale_ = scale; }
            inline void SetVelocity(const glm::vec3& velocity) { velocity_ = velocity; }

        protected:
            
            // Object's Transform Variables
            glm::vec3 position_;
            float scale_;
            glm::vec3 velocity_;
            // TODO: Add more transformation variables

            // Geometry
            Geometry *geometry_;
 
            // Shader
            Shader *shader_;

            // Object's texture reference
            GLuint texture_;

			ObjType type_;

            int unique_id_;

			std::vector<GameObject*> children_;


			// Static members

            
			// id counter
            static int id_counter_;

			// Get next unique id and increment counter
            static int GetNextId(void) {
                return id_counter_++;
            }

            // static const hashmap of ids to game objects
            static std::unordered_map<int, GameObject *> id_map_;

            static GameObject* GetObjById(int id) {
                return id_map_[id];
            }
            
            

    }; // class GameObject

} // namespace game

#endif // GAME_OBJECT_H_
