#ifndef GUI_H_
#define GUI_H_

#include "game_object.h"
#include "gui_elem.h"
#include "gui_state.h"

namespace game {
	class Gui : public GameObject
	{
	public:
		Gui(Geometry* geom, Shader* shader, GLFWwindow* window);

		void InitGui();

		void Update(double delta_time, GuiState* gui_state) override;

		void AddGuiElem(GuiElem* elem);
		void AddCrewGuiElem(GuiElem* elem);


	protected:
		// Vector of Gui elements
		std::vector<GuiElem*> gui_elems_;

		// Vector of Crew Gui elements
		std::vector<GuiElem*> crew_gui_elems_;

		// Pointer to Window
		GLFWwindow* window_;
	};
}

#endif