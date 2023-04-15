#include "airship_segment.h"

namespace game {
	AirshipSegment::AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : Collidable(position, geom, shader, texture) {
		type_ = ObjType::AIRSHIP_SEGMENT;
		z_layer_ = 10;
		num_workstations_ = 1;
		health_ = 1.0f;

	}


	void AirshipSegment::Update(double delta_time) {
		Collidable::Update(delta_time);
	}


	bool AirshipSegment::AssignCrew(Crew* crew) {
		if (workstations_.size() >= num_workstations_) return false;
		if (crew->GetActivityState() == ActivityState::MOVING) return false;
		for (int i = 0; i < workstations_.size(); i++) {
			if (!workstations_[i]->IsOccupied()) {
				workstations_[i]->AssignCrew(crew);
				SetCrewDestination(crew, workstations_[i]);
				return true;
			}
		}
		std::cout << "Error: Segment assigned crew < max_crew_, but all workstations are occupied. SHOULD NOT BE REACHED";
		return false;
	}

	bool AirshipSegment::UnassignCrew(Crew* crew) {
		int id = crew->GetID();
		for (int i = 0; i < workstations_.size(); i++) {
			if (workstations_[i]->GetCrew()->GetID() == id) {
				workstations_[i]->UnassignCrew();
				return true;
			}
		}
		// No crew member matching the one given exists in this segment
		return false;
	}

	void AirshipSegment::SetCrewDestination(Crew* crew, Workstation* workstation) {
		// TODO: Set destination of crew to the workstation
		crew->SetDestination(workstation->GetPosition() + GetPosition());

		
	}

	void AirshipSegment::AddWorkstation(Workstation* workstation) {
		workstations_.push_back(workstation);
		AddChild(workstation);
		num_workstations_++;
	}

	bool AirshipSegment::RemoveWorkstation(Workstation* workstation) {
		for (int i = 0; i < workstations_.size(); i++) {
			if (workstations_[i] == workstation) {
				workstations_.erase(workstations_.begin() + i);
				num_workstations_--;
				return true;
			}
		}
		return false;
	}

	void AirshipSegment::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case COLLIDABLE:
			dbg_render_red_ = true;
			break;
		case BULLET_ENEMY:
			dbg_render_red_ = true;
			break;
		case BIGBULLET_ENEMY:
			dbg_render_red_ = true;
			break;
		}
	}

	void AirshipSegment::HandleNewCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case COLLIDABLE:
			// Collision just started
			health_ -= 0.1f;
			for (int i = 0; i < workstations_.size(); i++) {
				if (workstations_[i]->IsOccupied()) {
					Crew* c = workstations_[i]->GetCrew();
					c->SetHealth(c->GetHealth() - 0.1f);
				}
			}
			break;

		case BULLET_ENEMY:
			health_ -= 0.1f;
			for (int i = 0; i < workstations_.size(); i++) {
				if (workstations_[i]->IsOccupied()) {
					Crew* c = workstations_[i]->GetCrew();
					c->SetHealth(c->GetHealth() - 0.1f);
				}
			}
			break;

		case BIGBULLET_ENEMY:
			health_ -= 0.2f;
			for (int i = 0; i < workstations_.size(); i++) {
				if (workstations_[i]->IsOccupied()) {
					Crew* c = workstations_[i]->GetCrew();
					c->SetHealth(c->GetHealth() - 0.2f);
				}
			}
			break;
		}
	}
}