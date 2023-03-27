#include "textures.h"

namespace game {


	Textures::Textures(void) {
		// Do nothing
	}
	
	Textures::~Textures(void) {
		// Do nothing
	}

	GLuint Textures::GetTexture(int index) const {
		return textures_[index];
	}

	GLuint Textures::GetTexture(std::string name) const {
		return texture_map_.at(name);
	}

	void Textures::InitTextures(void) {
		// Load textures
		// Load all textures that we will need
		glGenTextures(NUM_TEXTURES, textures_);
		SetTexture(textures_[0], (resources_directory_g + std::string("/textures/player_ship.png")).c_str());
		texture_map_["player_ship"] = textures_[0];
		SetTexture(textures_[1], (resources_directory_g + std::string("/textures/stars.png")).c_str());
		texture_map_["stars"] = textures_[1];
		SetTexture(textures_[2], (resources_directory_g + std::string("/textures/green_guy_ufo.png")).c_str());
		texture_map_["green_guy_ufo"] = textures_[2];
		SetTexture(textures_[3], (resources_directory_g + std::string("/textures/collision_circle.png")).c_str());
		texture_map_["collision_circle"] = textures_[3];
		SetTexture(textures_[4], (resources_directory_g + std::string("/textures/spinner.png")).c_str());
		texture_map_["spinner"] = textures_[4];
		glBindTexture(GL_TEXTURE_2D, textures_[0]);

	}

	void Textures::SetTexture(GLuint w, const char* fname) {
		// Load texture
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
	
}