#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "game_object.h"

namespace game {
    

int GameObject::id_counter_ = 0;

std::unordered_map<int, GameObject*> GameObject::id_map_;

GameObject::GameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture) 
{

    // Initialize all attributes
    position_ = position;
	rotation_ = 0.0f;
	orbit_rotation_ = 0.0f;
	scale_ = glm::vec2(1.0f, 1.0f);
    velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
    state_ = HOMING;
    geometry_ = geom;
    shader_ = shader;
    texture_ = texture;
    type_ = ObjType::OBJ;
    dbg_render_red_ = false;
	unique_id_ = GetNextId();

    id_map_[unique_id_] = this;

    
}
GameObject::~GameObject() {
	id_map_.erase(unique_id_);
	for (int i = 0; i < children_.size(); i++) {
		delete children_[i];
	}
}


void GameObject::Update(double delta_time) {

    // Update object position with Euler integration
	velocity_ += acceleration_ * ((float)delta_time);
    position_ += velocity_ * ((float) delta_time);
    GenerateTransformationMatrix();
    
	// Update all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->Update(delta_time);
	}

}


void GameObject::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, double current_time) {


    GenerateTransformationMatrix();
    global_transformation_ = parent_matrix * model_transformation_;

    glm::vec4 g_pos_vec4 = global_transformation_ * glm::vec4(position_, 1.0f);
    global_position_ = glm::vec3(g_pos_vec4.x, g_pos_vec4.y, g_pos_vec4.z);

    if (geometry_ != NULL && shader_ != NULL && texture_ != NULL) {

        // Set up the shader
        shader_->Enable();

        // Set up the view matrix
        shader_->SetUniformMat4("view_matrix", view_matrix);

        // Set the transformation matrix in the shader
        shader_->SetUniformMat4("transformation_matrix", global_transformation_);

        shader_->SetUniform1i("dbg_red", dbg_render_red_ ? 1 : 0);

        // Set up the geometry
        geometry_->SetGeometry(shader_->GetShaderProgram());

        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
    }

	// Render all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->Render(view_matrix, global_transformation_, current_time);
	}
}

void GameObject::GenerateTransformationMatrix(void) {

    // Set up the translation matrix
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    // Set up the orbit matrix
    glm::mat4 orbit_matrix = glm::rotate(glm::mat4(1.0f), orbit_rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

    // Setup the rotation matrix
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));


	// Setup the scaling matrix
	glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_.x, scale_.y, 1.0));

	// Setup the transformation matrix
	model_transformation_ = orbit_matrix * translation_matrix * rotation_matrix * scaling_matrix;
}

void GameObject::AddChild(GameObject* child) {
    children_.push_back(child);
}

void GameObject::HomeInOnPoint(const glm::vec3& target_position, glm::vec3& target_velocity, float delta_time) {

    if (state_ != HOMING) return;

	glm::vec2 curr_pos = glm::vec2(position_.x, position_.y);
	glm::vec2 target_pos = glm::vec2(target_position.x, target_position.y);

	glm::vec2 curr_vel = glm::vec2(velocity_.x, velocity_.y);
	glm::vec2 target_vel = glm::vec2(target_velocity.x, target_velocity.y);
    
    float deltaX = target_pos.x - curr_pos.x;
	float deltaY = target_pos.y - curr_pos.y;

	float dist = glm::sqrt(deltaX * deltaX + deltaY * deltaY);

	if (dist < glm::length(curr_vel) * delta_time) {
		acceleration_.x = 0.0f;
		acceleration_.y = 0.0f;
        velocity_.x = target_vel.x;
		velocity_.y = target_vel.y;
		position_.x = target_pos.x;
		position_.y = target_pos.y;
        state_ = DEFAULT;
        return;
	}

    float velMagSq = glm::length(curr_vel) * glm::length(curr_vel);
	//float targetVelMagSq = glm::length(target_vel) * glm::length(target_vel);
    
    float decelDist = (velMagSq) / (2 * max_accel_);
       

    if (dist >= decelDist) {
        acceleration_ = glm::vec3(glm::normalize(glm::vec2(deltaX, deltaY)) * max_accel_, 0.0f);
    }
    else {
        acceleration_ = glm::vec3(glm::normalize(glm::vec2(deltaX, deltaY)) * -max_accel_, 0.0f);

    }


    

    
}


} // namespace game

