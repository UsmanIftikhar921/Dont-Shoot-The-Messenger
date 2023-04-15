#ifndef ENGINE_POWER_GUI_ELEM_H_
#define ENGINE_POWER_GUI_ELEM_H_

#include "clickable_gui_elem.h"

namespace game {

	/* Background: */
	class EnginePowerGuiBackground : public GuiElem {
	public:
		EnginePowerGuiBackground(Geometry* geom, Shader* shader, GLFWwindow* window);
		virtual void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Top Green: */
	class TopGreenElem : public ClickableGuiElem {
	public:
		TopGreenElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Top Orange: */
	class TopOrangeElem : public ClickableGuiElem {

	public:
		TopOrangeElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Top Red Elem: */
	class TopRedElem : public ClickableGuiElem {

	public:
		TopRedElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Grey Elem */
	class GreyElem : public ClickableGuiElem {

	public:
		GreyElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Bottom Red Elem: */
	class BottomRedElem : public ClickableGuiElem {

	public:
		BottomRedElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Bottom Orange Elem */
	class BottomOrangeElem : public ClickableGuiElem {

	public:
		BottomOrangeElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Bottom Green Elem */
	class BottomGreenElem : public ClickableGuiElem {

	public:
		BottomGreenElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	class SelectorElem : public GuiElem {

	public:
		SelectorElem(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;

	protected:
	};
}
#endif