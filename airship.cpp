#include "airship.h"

namespace game {

	Airship::Airship(const glm::vec3& position) : GameObject(position) {
		type_ = ObjType::AIRSHIP;
	}

	void Airship::Update(double delta_time)  {
		GameObject::Update(delta_time);
	}

	void Airship::InitSegments(Geometry* geom, Shader* shader, std::vector<GLuint>* segment_textures) {
		
		port_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(0));
		starboard_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(1));
		bow_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(2));
		stern_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(3));
		port_engine_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(4));
		starboard_engine_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(5));
		boiler_room_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, segment_textures->at(6));

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

	void Airship::InitCrew(Geometry* geom, Shader* shader, GLuint texture) {
		glm::vec3 pos = bow_guns_->GetPosition();
		Crew* crew_ = new Crew(pos, geom, shader, texture);
		crew_members_.push_back(crew_);
		AddChild(crew_);
		
	}

}