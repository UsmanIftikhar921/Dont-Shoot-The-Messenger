#ifndef CLICKABLE_SHIP_SEGMENTS_H_
#define CLICKABLE_SHIP_SEGMENTS_H_

#include "clickable_gui_elem.h"

namespace game {

	/* Head: */
	class ClickableHead : public ClickableGuiElem {

	public:
		ClickableHead(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Front Body (Left): */
	class ClickableFrontBodyLeft : public ClickableGuiElem {

	public:
		ClickableFrontBodyLeft(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Front Body (Right): */
	class ClickableFrontBodyRight : public ClickableGuiElem {

	public:
		ClickableFrontBodyRight(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Left Tail */
	class ClickableLeftTail : public ClickableGuiElem {

	public:
		ClickableLeftTail(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Right Tail */
	class ClickableRightTail : public ClickableGuiElem {

	public:
		ClickableRightTail(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Rear Outer */
	class ClickableRearOuter : public ClickableGuiElem {

	public:
		ClickableRearOuter(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	/* Rear Inner */
	class ClickableRearInner : public ClickableGuiElem {

	public:
		ClickableRearInner(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
	};

	class ClickableRear : public GuiElem {

	public:
		ClickableRear(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput(GuiState* gui_state) override;
		ClickableRearOuter* GetRearOuter() { return rear_outer_; }
		ClickableRearInner* GetRearInner() { return rear_inner_; }

	protected:
		ClickableRearOuter* rear_outer_;
		ClickableRearInner* rear_inner_;
	};

}

#endif