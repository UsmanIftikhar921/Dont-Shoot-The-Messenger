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
#include "player_game_object.h"
#include "game.h"
#include "collision_box.h"


namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Globals that define the OpenGL window and viewport
const char *window_title_g = "Game Demo";
const unsigned int window_width_g = 1920;
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
    for (int i = 0; i < game_objects_.size(); i++){
        delete game_objects_[i];
    }

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
    game_objects_.push_back(new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[0], 0.3));
	game_objects_.push_back(new CollidableGameObject(glm::vec3(3.0f, 3.0f, 0.0f), sprite_, &sprite_shader_, tex_[2], 0.3));

    // Setup other objects
    

    // Setup background
    // In this specific implementation, the background is always the
    // last object
    GameObject *background = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[1]);
    background->SetScale(10.0);
    game_objects_.push_back(background);
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height)
{

    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);
}


void Game::SetTexture(GLuint w, const char *fname)
{
    // Bind texture buffer
    glBindTexture(GL_TEXTURE_2D, w);

    // Load texture from a file to the buffer
    int width, height;
    unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Game::SetAllTextures(void)
{
    // Load all textures that we will need
    glGenTextures(NUM_TEXTURES, tex_);
    SetTexture(tex_[0], (resources_directory_g+std::string("/textures/player_ship.png")).c_str());
	SetTexture(tex_[1], (resources_directory_g + std::string("/textures/stars.png")).c_str());
	SetTexture(tex_[2], (resources_directory_g + std::string("/textures/green_guy_ufo.png")).c_str());
    glBindTexture(GL_TEXTURE_2D, tex_[0]);
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

	// Update game objects
	for (int i = 0; i < game_objects_.size(); i++) {
		game_objects_[i]->Update(delta_time);
	}

	// Render game objects
	for (int i = 0; i < game_objects_.size(); i++) {
		game_objects_[i]->Render(view_matrix, delta_time);
	}
}


void Game::Controls(double delta_time)
{
    
	float move_speed = 1.0f;
    
    // Get player game object
    GameObject *player = game_objects_[0];
    // Get current position
    glm::vec3 curpos = player->GetPosition();
    // Set standard forward and right directions
    glm::vec3 dir = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
    
    // move player with wasd keys
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
        player->SetVelocity(dir * move_speed);
    }
    
	else if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
		player->SetVelocity(-dir * move_speed);
	}

    
	else if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
		player->SetVelocity(-right * move_speed);
	}

    
	else if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
		player->SetVelocity(right * move_speed);
	}
    else {
		player->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
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

