#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "game_object.h"

namespace game {
    

int GameObject::id_counter_ = 0;

std::unordered_map<int, GameObject*> GameObject::id_map_;

Textures GameObject::textures;

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
	color_modifier_ = glm::vec3(1.0f, 1.0f, 1.0f);

	z_layer_ = 0;
    
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
	position_.z = (float)z_layer_ / 100.0f;
    GenerateTransformationMatrix();
    
	// Update all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->Update(delta_time);
	}

}


void GameObject::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) {

    GenerateTransformationMatrix();

	glm::mat4 model_matrix = model_orbit_ * model_translation_ * model_rotation_;

	glm::vec4 g_pos = parent_matrix * model_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    global_position_ = glm::vec3(g_pos.x, g_pos.y, g_pos.z);

    glm::mat4 g_rotation = parent_matrix * model_orbit_ * model_rotation_;
	global_rotation_ = glm::atan(g_rotation[1][0], -g_rotation[0][0]);

    if (geometry_ != NULL && shader_ != NULL && texture_ != NULL) {

        // Set up the shader
        shader_->Enable();

        // Set up the view matrix
        shader_->SetUniformMat4("view_matrix", view_matrix);

        // Set the transformation matrix in the shader
		shader_->SetUniformMat4("transformation_matrix", parent_matrix * parent_scale_matrix * model_matrix * model_scale_);

        shader_->SetUniform1i("dbg_red", dbg_render_red_ ? 1 : 0);
        
		shader_->SetUniform3f("color_modifier", color_modifier_);

        // Set up the geometry
        geometry_->SetGeometry(shader_->GetShaderProgram());

        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
    }

	// Render all children
	for (int i = 0; i < children_.size(); i++) {
		children_[i]->Render(view_matrix, parent_matrix * model_matrix, parent_scale_matrix * model_scale_, current_time);
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


    
    // Set the matrices
	model_scale_ = scaling_matrix;
	model_rotation_ = rotation_matrix;
    model_translation_ = translation_matrix;
	model_orbit_ = orbit_matrix;
}

void GameObject::AddChild(GameObject* child) {
    children_.push_back(child);
}

glm::vec3 GameObject::GetBearing(void) {
	return glm::vec3(cos(rotation_), sin(rotation_), 0.0f);
}

} // namespace game

