#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"
#include "game_object.h"
#include "collision_box.h"
#include "gui.h"
#include "gui_state.h"

namespace game {

    // A class for holding the main game objects
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();

            // Call Init() before calling any other method
            // Initialize graphics libraries and main window
            void Init(void); 

            // Set up the game (scene, game objects, etc.)
            void Setup(void);

            // Run the game (keep the game active)
            void MainLoop(void); 

            void Exit(void);

        private:
            // Main window: pointer to the GLFW window structure
            GLFWwindow *window_;

            // Sprite geometry
            Geometry *sprite_;

            // Shader for rendering sprites in the scene
            Shader sprite_shader_;

            // GUI
            Gui* gui_;

            // GUI State
            GuiState* gui_state_;

            bool gameover_;
            float gameover_time_;

            // List of game objects
            GameObject* scene_;
			GameObject* player_;
            
            // Keep track of time
            double current_time_;

            // Callback for when the window is resized
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Load all textures
            void SetAllTextures();

            // Handle user input
            void Controls(double delta_time);

            // Update the game based on user input and simulation
            void Update(glm::mat4 view_matrix, double delta_time);

    }; // class Game

} // namespace game

#endif // GAME_H_
