#ifndef WHEEL_GUI_ELEM_H_
#define WHEEL_GUI_ELEM_H_

#include "gui_elem.h"

namespace game {
	class WheelGuiElem : public GuiElem
	{
	public:
		WheelGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);

		void Update(double delta_time, GuiState gui_state) override;


	protected:


	};
}

#endif