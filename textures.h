#ifndef TEXTURES_H_
#define TEXTURES_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <path_config.h>
#include <vector>
#include <unordered_map>
#include <string>

namespace game {
	class Textures {
	public:
		Textures(void);
		~Textures(void);
		GLuint GetTexture(int index) const;
		GLuint GetTexture(std::string name) const;
		void InitTextures(void);
		
		
	protected:
		void SetTexture(GLuint w, const char* fname);
#define NUM_TEXTURES 40
		GLuint textures_[NUM_TEXTURES];
		std::unordered_map<std::string, GLuint> texture_map_;
		std::string resources_directory_g = RESOURCES_DIRECTORY;
	};
}

#endif

