#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "clickable_gui_elem.h"

namespace game {

	/* Close Button: */
	class CloseButtonGuiElem : public ClickableGuiElem {

	public:
		CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);

		void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Other Button Class Definitions Go Here: */

}

#endif