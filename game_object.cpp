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
    scale_ = 1.0;
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
}


void GameObject::Update(double delta_time) {

    // Update object position with Euler integration
    position_ += velocity_ * ((float) delta_time);
    
	// Update all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->SetVelocity(velocity_);
		children_[i]->Update(delta_time);
	}

}


void GameObject::Render(glm::mat4 view_matrix, double current_time){

	if (geometry_ == NULL || shader_ == NULL || texture_ == NULL) {
		return;
	}

    // Set up the shader
    shader_->Enable();

    // Set up the view matrix
    shader_->SetUniformMat4("view_matrix", view_matrix);

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix = translation_matrix * scaling_matrix;

    // Set the transformation matrix in the shader
    shader_->SetUniformMat4("transformation_matrix", transformation_matrix);

	shader_->SetUniform1i("dbg_red", dbg_render_red_ ? 1 : 0);

    // Set up the geometry
    geometry_->SetGeometry(shader_->GetShaderProgram());

    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);

	// Render all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->Render(view_matrix, current_time);
	}
}


} // namespace game

