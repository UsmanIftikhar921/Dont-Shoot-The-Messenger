#ifndef GUI_ELEM_COLLECTION_H_
#define GUI_ELEM_COLLECTION_H_

#include "gui_elem.h"
#include "crew_status_gui_elem.h"

namespace game {
	class BackgroundGuiElem : public GuiElem {
	public:
		BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	class CrewGuiElem : public GuiElem {
	public:
		static int crew_count;

		CrewGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;

	private:
		CrewStatusBgElem* crew_status_bg_elem_;
		CrewStatusHealthElem* crew_status_health_elem_;
		CrewStatusPositionElem* crew_status_position_elem_;
	};
}

#endif