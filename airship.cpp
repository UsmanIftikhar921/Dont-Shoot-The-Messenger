#include "airship.h"
#include <iostream>

namespace game {

	Airship::Airship(const glm::vec3& position, Geometry* geom, Shader* shader) : GameObject(position) {
		type_ = ObjType::AIRSHIP;
		geometry_ = geom;
		shader_ = shader;
		InitSegments();
		InitCrew();
	}

	void Airship::Update(double delta_time)  {		
		GameObject::Update(delta_time);
	}

	void Airship::InitSegments() {

		Geometry* geom = geometry_;
		Shader* shader = shader_;

		
		
		port_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(5));
		starboard_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(6));
		bow_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(7));
		stern_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(8));
		port_engine_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(9));
		starboard_engine_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(10));
		boiler_room_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(11));

		port_guns_->SetPosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		starboard_guns_->SetPosition(glm::vec3(0.1f, 0.0f, 0.0f));
		bow_guns_->SetPosition(glm::vec3(0.0f, 0.3f, 0.0f));
		stern_guns_->SetPosition(glm::vec3(0.0f, -0.34f, 0.0f));
		port_engine_->SetPosition(glm::vec3(-0.35f, -0.33f, 0.0f));
		starboard_engine_->SetPosition(glm::vec3(0.35f, -0.33f, 0.0f));
		boiler_room_->SetPosition(glm::vec3(0.0f, -0.29f, 0.0f));


		segments_.push_back(port_guns_);
		segments_.push_back(starboard_guns_);
		segments_.push_back(port_engine_);
		segments_.push_back(starboard_engine_);
		segments_.push_back(bow_guns_);
		segments_.push_back(boiler_room_);
		segments_.push_back(stern_guns_);

		AddChild(port_guns_);
		AddChild(starboard_guns_);
		AddChild(bow_guns_);
		AddChild(stern_guns_);
		AddChild(port_engine_);
		AddChild(starboard_engine_);
		AddChild(boiler_room_);
	}

	void Airship::InitCrew() {
		Geometry* geom = geometry_;
		Shader* shader = shader_;
		glm::vec3 pos = starboard_engine_->GetPosition();
		Crew* crew_ = new Crew(pos, geom, shader, GameObject::textures.GetTexture(12));
		crew_members_.push_back(crew_);
		AddChild(crew_);
		
	}

	void Airship::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) {
		GameObject::Render(view_matrix, parent_matrix, parent_scale_matrix, current_time);
	}

}