#ifndef GUI_STATE_H_
#define GUI_STATE_H_

namespace game {
	class GuiState : public GameObject
	{
	public:
		GuiState(Geometry* geom, Shader* shader);

		void Update(double delta_time, GLFWwindow* window) override;


	protected:

	};
}

#endif