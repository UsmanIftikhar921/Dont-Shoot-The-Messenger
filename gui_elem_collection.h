#ifndef GUI_ELEM_COLLECTION_H_
#define GUI_ELEM_COLLECTION_H_

#include "gui_elem.h"
#include "crew_status_gui_elem.h"
#include "engine_power_gui_elem.h"

namespace game {
	class BackgroundGuiElem : public GuiElem {
	public:
		BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	class CrewGuiElem : public GuiElem {
	public:
		static int crew_count;
		CrewGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;

	private:
		CrewStatusBgElem* crew_status_bg_elem_;
		CrewStatusHealthElem* crew_status_health_elem_;
		CrewStatusPositionElem* crew_status_position_elem_;
	};

	/* Engine Power: */
	class EnginePowerGuiElem : public GuiElem {
	public:
		EnginePowerGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;

	private:
		EnginePowerGuiBackground* engine_power_gui_background_;

		TopGreenElem* top_green_elem_;
		TopOrangeElem* top_orange_elem_;
		TopRedElem* top_red_elem_;
		GreyElem* grey_elem_;
		BottomRedElem* bottom_red_elem_;
		BottomOrangeElem* bottom_orange_elem_;
		BottomGreenElem* bottom_green_elem_;
	};

}

#endif