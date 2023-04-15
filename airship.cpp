#include "airship.h"
#include <iostream>

namespace game {

	Airship::Airship(const glm::vec3& position, Geometry* geom, Shader* shader) : GameObject(position) {
		type_ = ObjType::AIRSHIP;
		geometry_ = geom;
		shader_ = shader;

		max_velocity_ = 5.0f;
		max_angular_velocity_ = 0.5f;

		timer_ = 0.0f;

		InitSegments();
		InitCrew();

		powerup_ = false;



	}

	void Airship::Update(double delta_time, GuiState* gui_state)  {	

		port_engine_->SetTargetPower(gui_state->GetPortEnginePower() * 2.0f);
		starboard_engine_->SetTargetPower(gui_state->GetStarboardEnginePower() * 2.0f);

		float port_engine_power = port_engine_->GetPower();
		float starboard_engine_power = starboard_engine_->GetPower();

		float port_engine_rotation_factor = port_engine_->GetRotationFactor();
		float starboard_engine_rotation_factor = starboard_engine_->GetRotationFactor();


		acceleration_ = glm::vec3(0.0f, port_engine_power + starboard_engine_power, 0.0f);
		acceleration_ = glm::rotate(acceleration_, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
		
		angular_acceleration_ = port_engine_rotation_factor + starboard_engine_rotation_factor;

		// decrease angular velocity by a bit
		angular_velocity_ *= 0.99f;
		
		// Update Segments
		FireSelector fs = gui_state->GetFireSelector();
		port_guns_->SetDisable(!fs.port);
		starboard_guns_->SetDisable(!fs.starboard);
		stern_guns_->SetDisable(!fs.stern);

		// Update Crew
		// If all crew are dead, exit
		bool all_dead = true;
		for (int i = 0; i < crew_members_.size(); i++) {
			if (crew_members_[i]->GetHealth() > 0.0f) {
				all_dead = false;
				break;
			}
		}
		if (all_dead) {
			std::cout << "All crew members are dead. Game over." << std::endl;
			exit(0);
		}


		std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();

		// print CrewData in crew_data vec
		//std::cout << "Crew data vec size: " << crew_data.size() << std::endl;
		//for (int i = 0; i < crew_data.size(); i++) {
		//	std::cout << "	Crew member " << i << " health: " << crew_data[i].health << std::endl;
		//	std::cout << "	Crew member " << i << " alive: " << crew_data[i].alive << std::endl;
		//	std::cout << "	Crew member " << i << " assigned segment: " << crew_data[i].assigned_segment << std::endl;
		//}


		if (crew_data.size() != crew_members_.size()) {
			// Crew has been added or removed
			// Update crew_members_ vector
			crew_data.clear();
			for (int i = 0; i < crew_members_.size(); i++) {
				CrewData data;
				data.health = crew_members_[i]->GetHealth();
				data.alive = crew_members_[i]->GetHealth() > 0.0f;
				data.assigned_segment = UNASSIGNED;
				crew_data.push_back(data);
			}
			gui_state->SetCrewDataVec(crew_data);

		}
		else {
			// Crew has not been added or removed
			// Update health of crew members
			for (int i = 0; i < crew_data.size(); i++) {
				crew_data[i].health = crew_members_[i]->GetHealth();
				crew_data[i].alive = crew_members_[i]->GetHealth() > 0.0f;
			}
		}

		for (int i = 0; i < crew_members_.size(); i++) {
			Segment assigned_segment = crew_data[i].assigned_segment;

			// Upate crew member health
			CrewData data;
			data.health = crew_members_[i]->GetHealth();
			data.alive = crew_members_[i]->GetHealth() > 0.0f;
			data.assigned_segment = assigned_segment;

			crew_data[i] = data;

			switch (assigned_segment) {
				case UNASSIGNED:
					// Do nothing
					break;

				case PORT_GUNS:
					if (!port_guns_->HasCrew(crew_members_[i]))
					port_guns_->AssignCrew(crew_members_[i]);
					break;

				case STARBOARD_GUNS:
					if (!starboard_guns_->HasCrew(crew_members_[i])) {
						starboard_guns_->AssignCrew(crew_members_[i]);
					}
					break;

				case BOILER: // Stern guns and boiler are flipped, gui code is spaghettie, this works leave me alone
					if (!stern_guns_->HasCrew(crew_members_[i]))
					stern_guns_->AssignCrew(crew_members_[i]);
					break;

				case PORT_ENGINE:
					if (!port_engine_->HasCrew(crew_members_[i]))
					port_engine_->AssignCrew(crew_members_[i]);
					break;

				case STARBOARD_ENGINE:
					if (!starboard_engine_->HasCrew(crew_members_[i]))
					starboard_engine_->AssignCrew(crew_members_[i]);
					break;

				case BOW:
					if (!bow_guns_->HasCrew(crew_members_[i]))
					bow_guns_->AssignCrew(crew_members_[i]);
					break;

				case STERN_GUNS: // Stern guns and boiler are flipped, gui code is spaghettie, this works leave me alone
					if (!boiler_room_->HasCrew(crew_members_[i]))
						boiler_room_->AssignCrew(crew_members_[i]);
					break;
			}
		}

		gui_state->SetCrewDataVec(crew_data);



		// Check if any segments have powerups
		for (int i = 0; i < segments_.size(); i++) {
			if (segments_[i]->powerup_pickup) {
				powerup_ = true;
				segments_[i]->powerup_pickup = false;
				timer_ = 10.0f;

				for (int j = 0; j < crew_members_.size(); j++) {
					crew_members_[j]->SetEffMultiplier(2.0f);
				}
				break;
			}
		}

		if (powerup_ = true) {
			timer_ -= delta_time;
			if (timer_ <= 0.0f) {
				powerup_ = false;
				for (int i = 0; i < crew_members_.size(); i++) {
					crew_members_[i]->SetEffMultiplier(1.0f);
				}
			}
		}

		
		GameObject::Update(delta_time, gui_state);
	}



	void Airship::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) {
		GameObject::Render(view_matrix, parent_matrix, parent_scale_matrix, current_time);
	}

	Crew* Airship::GetCrewMember(int index) {
		if (index < 0 || index >= crew_members_.size()) {
			return nullptr;
		}
		return crew_members_[index];
	}

	void Airship::InitCrew() {
		Geometry* geom = geometry_;
		Shader* shader = shader_;

		Crew* crew_ = new Crew(position_, geom, shader, GameObject::textures.GetTexture(12));
		crew_->SetScale(glm::vec2(0.03f, 0.03f));
		crew_members_.push_back(crew_);
		AddChild(crew_);
		//stern_guns_->AssignCrew(crew_);

		Crew* crew_2 = new Crew(position_, geom, shader, GameObject::textures.GetTexture(12));
		crew_2->SetScale(glm::vec2(0.03f, 0.03f));
		crew_members_.push_back(crew_2);
		AddChild(crew_2);
		//port_guns_->AssignCrew(crew_2);

		Crew* crew_3 = new Crew(position_, geom, shader, GameObject::textures.GetTexture(12));
		crew_3->SetScale(glm::vec2(0.03f, 0.03f));
		crew_members_.push_back(crew_3);
		AddChild(crew_3);
		//starboard_guns_->AssignCrew(crew_3);

	}

	void Airship::InitSegments() {

		Geometry* geom = geometry_;
		Shader* shader = shader_;



		port_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(5));
		starboard_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(6));
		bow_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(7));
		stern_guns_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(8));
		port_engine_ = new Engine(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(9), 1.0f, -0.5f);
		starboard_engine_ = new Engine(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(10), 1.0f, 0.5f);
		boiler_room_ = new AirshipSegment(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, GameObject::textures.GetTexture(11));

		port_guns_->SetPosition(glm::vec3(-0.3f, 0.0f, 0.0f));
		starboard_guns_->SetPosition(glm::vec3(0.3f, 0.0f, 0.0f));
		bow_guns_->SetPosition(glm::vec3(0.0f, 0.9f, 0.0f));
		stern_guns_->SetPosition(glm::vec3(0.0f, -1.07f, 0.0f));
		port_engine_->SetPosition(glm::vec3(-1.0f, -1.0f, 0.0f));
		starboard_engine_->SetPosition(glm::vec3(1.0f, -1.0f, 0.0f));
		boiler_room_->SetPosition(glm::vec3(0.0f, -0.88f, 0.0f));

		port_guns_->InitCollisionBox(glm::vec3(0), 0.6f, 1.0f);
		starboard_guns_->InitCollisionBox(glm::vec3(0), 0.6f, 1.0f);
		bow_guns_->InitCollisionBox(glm::vec3(0.0f, -0.1f, 0.0f), 1.0f, 0.6f);
		stern_guns_->InitCollisionBox(glm::vec3(0.0f, 0.0f, 0.0f), 0.7f, 0.35f);
		port_engine_->InitCollisionBox(glm::vec3(-0.27f, -0.17f, 0.0f), 0.30f, 0.65f);
		starboard_engine_->InitCollisionBox(glm::vec3(0.27f, -0.17f, 0.0f), 0.30f, 0.65f);
		boiler_room_->InitCollisionBox(glm::vec3(0.0f, 0.18f, 0.0f), 1.2f, 0.35f);

		segments_.push_back(port_guns_);
		segments_.push_back(starboard_guns_);
		segments_.push_back(bow_guns_);
		segments_.push_back(stern_guns_); 
		segments_.push_back(boiler_room_);
		segments_.push_back(port_engine_);
		segments_.push_back(starboard_engine_);

		port_engine_->SetTargetPower(5.0f);
		starboard_engine_->SetTargetPower(5.0f);
		

		AddChild(port_guns_);
		AddChild(starboard_guns_);
		AddChild(bow_guns_);
		AddChild(stern_guns_);
		AddChild(boiler_room_);
		AddChild(port_engine_);
		AddChild(starboard_engine_);
		

		// --- WORKSTATIONS --- //
		// Port Guns
		{
			glm::vec3 gun_pos = glm::vec3(-0.25f, 0.0f, 0.0f);

			// Workstation 1
			Task* gun1 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun1->SetZLayer(-2);
			gun1->SetCardinalRotation('W');
			gun1->SetScale(glm::vec2(2.0f, 2.0f));
			gun1->SetPosition(gun_pos);

			Workstation* w1 = new Workstation(glm::vec3(0.0, 0.0, 0.0), geom, shader, gun1);
			w1->SetZLayer(-1);
			w1->SetScale(glm::vec2(0.05f, 0.05f));
			w1->SetPosition(glm::vec3(0.0f, 0.35f, 0.0f));
			port_guns_->AddWorkstation(w1);


			// Workstation 2
			Task* gun2 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun2->SetZLayer(-2);
			gun2->SetCardinalRotation('W');
			gun2->SetScale(glm::vec2(2.0f, 2.0f));
			gun2->SetPosition(gun_pos);

			Workstation* w2 = new Workstation(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, gun2);
			w2->SetZLayer(-1);
			w2->SetScale(glm::vec2(0.05f, 0.05f));
			w2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			port_guns_->AddWorkstation(w2);


			// Workstation 3
			Task* gun3 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun3->SetZLayer(-2);
			gun3->SetCardinalRotation('W');
			gun3->SetScale(glm::vec2(2.0f, 2.0f));
			gun3->SetPosition(gun_pos);

			Workstation* w3 = new Workstation(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, gun3);
			w3->SetZLayer(-1);
			w3->SetScale(glm::vec2(0.05f, 0.05f));
			w3->SetPosition(glm::vec3(0.0f, -0.35f, 0.0f));
			port_guns_->AddWorkstation(w3);
		}
			
		
		// Starboard Guns
		{
			glm::vec3 gun_pos = glm::vec3(0.25f, 0.0f, 0.0f);

			// Workstation 1
			Task* gun11 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun11->SetZLayer(-2);
			gun11->SetCardinalRotation('E');
			gun11->SetScale(glm::vec2(2.0f, 2.0f));
			gun11->SetPosition(gun_pos);

			Workstation* w1 = new Workstation(glm::vec3(0.0, 0.0, 0.0), geom, shader, gun11);
			w1->SetZLayer(-1);
			w1->SetScale(glm::vec2(0.05f, 0.05f));
			w1->SetPosition(glm::vec3(0.0f, 0.35f, 0.0f));
			starboard_guns_->AddWorkstation(w1);

			// Workstation 2
			Task* gun2 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun2->SetZLayer(-2);
			gun2->SetCardinalRotation('E');
			gun2->SetScale(glm::vec2(2.0f, 2.0f));
			gun2->SetPosition(gun_pos);

			Workstation* w2 = new Workstation(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, gun2);
			w2->SetZLayer(-1);
			w2->SetScale(glm::vec2(0.05f, 0.05f));
			w2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			starboard_guns_->AddWorkstation(w2);


			// Workstation 3
			Task* gun3 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true);
			gun3->SetZLayer(-2);
			gun3->SetCardinalRotation('E');
			gun3->SetScale(glm::vec2(2.0f, 2.0f));
			gun3->SetPosition(gun_pos);

			Workstation* w3 = new Workstation(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, gun3);
			w3->SetZLayer(-1);
			w3->SetScale(glm::vec2(0.05f, 0.05f));
			w3->SetPosition(glm::vec3(0.0f, -0.35f, 0.0f));
			starboard_guns_->AddWorkstation(w3);
		}

		// Stern Gun
		{
			glm::vec3 gun_pos = glm::vec3(0.0f, -0.25f, 0.0f);

			// Workstation 1
			Task* gun1 = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, true, GunType::HEAVY);
			gun1->SetZLayer(-2);
			gun1->SetCardinalRotation('S');
			gun1->SetScale(glm::vec2(2.0f, 2.0f));
			gun1->SetPosition(gun_pos);

			Workstation* w1 = new Workstation(glm::vec3(0.0, 0.0, 0.0), geom, shader, gun1);
			w1->SetZLayer(-1);
			w1->SetScale(glm::vec2(0.05f, 0.05f));
			w1->SetPosition(glm::vec3(0.0f, 0.07f, 0.0f));
			stern_guns_->AddWorkstation(w1);
		}

	}

}