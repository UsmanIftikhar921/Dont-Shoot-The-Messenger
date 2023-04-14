#ifndef CLICKABLE_SHIP_SEGMENTS_H_
#define CLICKABLE_SHIP_SEGMENTS_H_

#include "clickable_gui_elem.h"

namespace game {

	/* Head: */
	class ClickableHead : public ClickableGuiElem {

	public:
		ClickableHead(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	/* Front Body (Left): */
	class ClickableFrontBodyLeft : public ClickableGuiElem {

	public:
		ClickableFrontBodyLeft(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	/* Front Body (Right): */
	class ClickableFrontBodyRight : public ClickableGuiElem {

	public:
		ClickableFrontBodyRight(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	/* Left Tail */
	class ClickableLeftTail : public ClickableGuiElem {

	public:
		ClickableLeftTail(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	/* Right Tail */
	class ClickableRightTail : public ClickableGuiElem {

	public:
		ClickableRightTail(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
	};

	/* Rear Outer */
	class ClickableRearOuter : public ClickableGuiElem {

	public:
		ClickableRearOuter(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
		bool getOuterHover() { return hover_; }
		void setOuterHover(bool hover) { hover_ = hover; }
	};

	/* Rear Inner */
	class ClickableRearInner : public ClickableGuiElem {

	public:
		ClickableRearInner(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;
		bool getInnerHover() { return hover_; }
		void setOuterHover(bool hover) { hover_ = hover; }
	};

	class ClickableRear : public GuiElem {

	public:
		ClickableRear(Geometry* geom, Shader* shader, GLFWwindow* window);
		void Update(double delta_time, GuiState* gui_state) override;
		virtual void ProcessInput() override;

	protected:
		ClickableRearOuter* rear_outer_;
		ClickableRearInner* rear_inner_;
	};

}

#endif