#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include "geometry.h"
#include "textures.h"

#include <unordered_map>
#include <string>

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of one object in the game world
        The update and render methods are virtual, so you can inherit them from GameObject and override the update or render functionality (see Player for reference)
    */

    enum ObjType {
        OBJ,
        PLAYER,
        BULLET,
        COLLIDABLE,
        COLLISION_BOX,
        SPINNER,
        AIRSHIP,
        AIRSHIP_SEGMENT,
        CREW,
    };
    
    class GameObject {

        public:
            // Constructor
            GameObject(const glm::vec3& position, Geometry* geom = NULL, Shader* shader = NULL, GLuint texture = NULL);
            ~GameObject();

            // Update the GameObject's state. Can be overriden in children
            virtual void Update(double delta_time);

            // Renders the GameObject 
            virtual void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time);

            void GenerateTransformationMatrix(void);
            
			void AddChild(GameObject* child);

            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline glm::vec2& GetScale(void) { return scale_; }
			inline float GetRotation(void) { return rotation_; }
			inline float GetOrbitRotation(void) { return orbit_rotation_; }
			inline int GetZLayer(void) { return z_layer_; }
			inline glm::vec3 GetVelocity(void) { return velocity_; }

            inline glm::vec3 GetGlobalPosition(void) { return global_position_; }
            
			inline glm::mat4 GetScaleMatrix(void) { return model_scale_; }
			inline glm::mat4 GetTranslationMatrix(void) { return model_translation_; }
			inline glm::mat4 GetRotationMatrix(void) { return model_rotation_; }
			inline glm::mat4 GetOrbitMatrix(void) { return model_orbit_; }
            
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline ObjType GetType(void) { return type_; }
			inline GameObject* GetChild(int index) { return children_[index]; }

            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetScale(glm::vec2& scale) { scale_ = scale; }
			inline void SetRotation(float rotation) { rotation_ = rotation; }
			inline void SetOrbitRotation(float orbit_rotation) { orbit_rotation_ = orbit_rotation; }
            inline void SetVelocity(const glm::vec3& velocity) { velocity_ = velocity; }
			inline void SetZLayer(int z_layer) { z_layer_ = z_layer; }

            static std::string& GetEnumName(ObjType type) {
                static std::string names[] = {
                    "OBJ",
                    "PLAYER",
                    "BULLET",
                    "COLLIDABLE",
                    "COLLISION_BOX",
                };
                return names[type];
            }

            static Textures textures;



        protected:
            
            // Object's Transform Variables
            glm::vec3 position_;
            glm::vec2 scale_;
            float rotation_;
            float orbit_rotation_;

            glm::vec3 global_position_;

			int z_layer_; // 0 - 100; 0 is furthest forward, 100 is furthest back

            glm::mat4 model_scale_;
			glm::mat4 model_rotation_;
			glm::mat4 model_orbit_;
			glm::mat4 model_translation_;
            
            glm::vec3 velocity_;

            // Geometry
            Geometry *geometry_;
 
            // Shader
            Shader *shader_;

            // Object's texture reference
            GLuint texture_;

			ObjType type_;

            int unique_id_;

			std::vector<GameObject*> children_;

            bool dbg_render_red_;

            glm::vec3 color_modifier_;

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
