#ifndef CREW_STATUS_GUI_ELEM_H_
#define CREW_STATUS_GUI_ELEM_H_

#include "gui_elem.h"
#include "clickable_ship_segments.h"

namespace game {
	class CrewStatusBgElem : public GuiElem {
	public:
		CrewStatusBgElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	class CrewStatusHealthElem : public GuiElem {
	public:
		CrewStatusHealthElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	class CrewStatusPositionElem : public GuiElem {
	public:
		CrewStatusPositionElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	private:
		ClickableHead* head;
		ClickableFrontBodyLeft* front_body_left;
		ClickableFrontBodyRight* front_body_right;
		ClickableLeftTail* left_tail;
		ClickableRightTail* right_tail;
		ClickableRearOuter* rear_outer;
		ClickableRearInner* rear_inner;
	};
}

#endif