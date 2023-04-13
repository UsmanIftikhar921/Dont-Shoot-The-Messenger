#ifndef GUI_ELEM_COLLECTION_H_
#define GUI_ELEM_COLLECTION_H_

#include "gui_elem.h"

namespace game {
	class BackgroundGuiElem : public GuiElem
	{
	public:
		BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 aspect_ratio);

		virtual void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput() override;

	protected:

	};
}

#endif