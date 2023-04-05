#ifndef GUI_ELEM_H_
#define GUI_ELEM_H_

#include "game_object.h"

namespace game {
	class GuiElem : public GameObject
	{
	public:
		GuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);

		void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput() = 0;


	protected:
		GLFWwindow* window_;
	};
}

#endif