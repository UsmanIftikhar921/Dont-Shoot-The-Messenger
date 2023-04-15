#ifndef GUI_ELEM_H_
#define GUI_ELEM_H_

#include "game_object.h"

namespace game {
	class GuiElem : public GameObject
	{
	public:
		GuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, GLuint texture = NULL);

		virtual void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput(GuiState* gui_state) = 0;

		virtual void SetColorModifier(glm::vec3 color) { color_modifier_ = color; }


	protected:
		GLFWwindow* window_;
	};
}

#endif