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

bool GameObject::ShouldIAccelerate(float curr_pos, float curr_speed, float accel, float target_pos, float target_speed, float delta_time){
    // Find distance between current position and target positon
    float distance = curr_pos - target_pos;
    float signed_accel = accel;

    // If we apply our acceleration negatively on every single frame, at what distance do we reach a velocity of zero (or less)
    float simulated_position = curr_pos;
    float simulated_speed = curr_speed;

    while(simulated_speed >= target_speed){
        simulated_position += simulated_speed;
        simulated_speed -= accel;
    }

    // Check simulated distance
    // Is that distance greater than or less than the target distance
    float simulation_final_distance = glm::abs(curr_pos - simulated_position);
    if(simulation_final_distance < distance ) return true;
    else return false;
}

void GameObject::HomeInOnPosition(const glm::vec3& target_position, float speed) {
    // Change object's velocity with an acceleration that changes depending on how close they are to the target position
    glm::vec3 direction = target_position - position_;
    float distance = glm::length(direction);
    direction = glm::normalize(direction);
    velocity_ = direction * speed * distance;
}


} // namespace game

