#ifndef CREW_STATUS_GUI_ELEM_H_
#define CREW_STATUS_GUI_ELEM_H_

#include "gui_elem.h"
#include "clickable_ship_segments.h"

namespace game {
	class CrewStatusBgElem : public GuiElem {
	public:
		CrewStatusBgElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	class CrewStatusHealthElem : public GuiElem {
	public:
		CrewStatusHealthElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	class CrewStatusPositionElem : public GuiElem {
	public:
		CrewStatusPositionElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	private:
		ClickableHead* head_;
		ClickableFrontBodyLeft* front_body_left_;
		ClickableFrontBodyRight* front_body_right_;
		ClickableLeftTail* left_tail_;
		ClickableRightTail* right_tail_;
		ClickableRear* rear_;
	};
}

#endif