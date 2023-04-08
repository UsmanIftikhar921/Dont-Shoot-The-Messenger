#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>

#include <path_config.h>
#include <string>

#include "sprite.h"
#include "shader.h"
#include "player.h"
#include "bullet.h"
#include "game.h"
#include "collision_box.h"
#include "spinner.h"
#include "airship.h"
#include "gun.h"


namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Globals that define the OpenGL window and viewport
const char *window_title_g = "Game Demo";
const unsigned int window_width_g = 1080;
const unsigned int window_height_g = 1080;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);


// Directory with game resources such as textures
const std::string resources_directory_g = RESOURCES_DIRECTORY;

constexpr unsigned int switch_pair(ObjType a, ObjType b) {
    return (a << 16) + b;
}


Game::Game(void)
{
    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void)
{

    // Initialize the window management library (GLFW)
    if (!glfwInit()) {
        throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
    }

    // Set window to not resizable
    // Required or else the calculation to get cursor pos to screenspace will be incorrect
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

    // Create a window and its OpenGL context
    window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
    if (!window_) {
        glfwTerminate();
        throw(std::runtime_error(std::string("Could not create window")));
    }

    // Make the window's OpenGL context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
    }

    // Set event callbacks
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Initialize sprite geometry
    sprite_ = new Sprite();
    sprite_->CreateGeometry();

    // Initialize sprite shader
    sprite_shader_.Init((resources_directory_g+std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/sprite_fragment_shader.glsl")).c_str());

    // Initialize time
    current_time_ = 0.0;

	gameover_ = false;
    gameover_time_ = 1.0;
}


Game::~Game()
{
    // Free memory for all objects
    // Only need to delete objects that are not automatically freed
    delete sprite_;

    // Close window
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void Game::Setup(void)
{

    // Setup the game world

    // Load textures
    SetAllTextures();

    // Setup the player object (position, texture, vertex count)
    // Note that, in this specific implementation, the player object should always be the first object in the game object vector 

    // The scene object is the parent of all other objects
	scene_ = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
    
	/*Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[0]);
    player->InitCollisionBox(0.25, sprite_, &sprite_shader_, tex_[3]);
	scene_->AddChild(player);
    


    // Fidget spinner added as example of heirarchical objects
	Spinner* spinner = new Spinner(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, GameObject::textures.GetTexture(4));
    spinner->SetScale(glm::vec2(0.5f, 0.5f));
    spinner->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));
    // Added as child of player
    player->AddChild(spinner);*/

    // GUI State
    gui_state_ = new GuiState();

    // GUI
    gui_ = new Gui(sprite_, &sprite_shader_, window_);
        
    // Airship
	Airship* airship = new Airship(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_);
    airship->SetZLayer(1);
    airship->SetScale(glm::vec2(3.0f, 3.0f));
    scene_->AddChild(airship);

    // Background
	GameObject* background = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, GameObject::textures.GetTexture(1));
    background->SetZLayer(100);
    background->SetScale(glm::vec2(10.0f, 10.0f));
	scene_->AddChild(background);
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height)
{

    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);
}


void Game::SetAllTextures(void)
{
	GameObject::textures.InitTextures();
}


void Game::MainLoop(void)
{
    // Loop while the user did not close the window
    double last_time = glfwGetTime();
    while (!glfwWindowShouldClose(window_)){

        // Clear background
        glClearColor(viewport_background_color_g.r,
                     viewport_background_color_g.g,
                     viewport_background_color_g.b, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set view to zoom out, centered by default at 0,0
        float camera_zoom = 0.25f;
        glm::mat4 view_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));

        // Calculate delta time
        double current_time = glfwGetTime();
        double delta_time = current_time - last_time;
        last_time = current_time;

        // Update other events like input handling
        glfwPollEvents();

        // Update the game
        Update(view_matrix, delta_time);

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);
    }
}


void Game::Update(glm::mat4 view_matrix, double delta_time)
{

    // Update time
    current_time_ += delta_time;

    // Handle user input
    Controls(delta_time);

	// Check for collisions
    CollisionBox::ProcessCollisions();

    // Update GUI 
    gui_->Update(delta_time, gui_state_);

	// Update game objects
	scene_->Update(delta_time, gui_state_);

    glm::mat4 identity = glm::mat4(1.0f);

    // Render GUI
    gui_->Render(identity, identity, identity, delta_time);

	// Render game objects
	scene_->Render(view_matrix, identity, identity, delta_time);
}


void Game::Controls(double delta_time)
{
    
	float move_speed = 1.0f;
    
    // Get player game object
    Airship* airship = dynamic_cast<Airship*>(scene_->GetChild(0));
    // Get current position
    glm::vec3 curpos = airship->GetPosition();
    // Set standard forward and right directions
    glm::vec3 dir = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

	if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
        airship->FirePortGun();
	}

    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
    
    // move player with wasd keys
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
        airship->SetVelocity(dir * move_speed);
    }
    
	else if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
        airship->SetVelocity(-dir * move_speed);
	}

    
	else if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
        airship->SetVelocity(-right * move_speed);
	}

    
	else if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
        airship->SetVelocity(right * move_speed);
	}

    else {
        airship->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    
	if (glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS) {
        airship->SetRotation(airship->GetRotation() + 0.8f * delta_time);
	}
    else if (glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        airship->SetRotation(airship->GetRotation() - 0.8f * delta_time);
    }




}

void Game::Exit(void) {
	// Close OpenGL window and terminate GLFW
	glfwDestroyWindow(window_);
	glfwTerminate();
    
	// Exit program
    std::cout << "Game over!" << std::endl;
	exit(EXIT_SUCCESS);
}

} // namespace game

