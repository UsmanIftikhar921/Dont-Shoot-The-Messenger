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
		
		SetTexture(textures_[1], (resources_directory_g + std::string("/textures/ocean.png")).c_str());
		texture_map_["ocean"] = textures_[1];
		
		SetTexture(textures_[2], (resources_directory_g + std::string("/textures/green_guy_ufo.png")).c_str());
		texture_map_["green_guy_ufo"] = textures_[2];
		
		SetTexture(textures_[3], (resources_directory_g + std::string("/textures/collision_circle.png")).c_str());
		texture_map_["collision_circle"] = textures_[3];
		
		SetTexture(textures_[4], (resources_directory_g + std::string("/textures/spinner.png")).c_str());
		texture_map_["spinner"] = textures_[4];
		
		SetTexture(textures_[5], (resources_directory_g + std::string("/textures/airship_segments/port_guns.png")).c_str());
		texture_map_["port_guns"] = textures_[5];

		SetTexture(textures_[6], (resources_directory_g + std::string("/textures/airship_segments/starboard_guns.png")).c_str());
		texture_map_["starboard_guns"] = textures_[6];

		SetTexture(textures_[7], (resources_directory_g + std::string("/textures/airship_segments/bow_guns.png")).c_str());
		texture_map_["bow_guns"] = textures_[7];
		
		SetTexture(textures_[8], (resources_directory_g + std::string("/textures/airship_segments/stern_guns.png")).c_str());
		texture_map_["stern_guns"] = textures_[8];
		
		SetTexture(textures_[9], (resources_directory_g + std::string("/textures/airship_segments/port_engine.png")).c_str());
		texture_map_["port_engine"] = textures_[9];
		
		SetTexture(textures_[10], (resources_directory_g + std::string("/textures/airship_segments/starboard_engine.png")).c_str());
		texture_map_["starboard_engine"] = textures_[10];

		SetTexture(textures_[11], (resources_directory_g + std::string("/textures/airship_segments/boiler_room.png")).c_str());
		texture_map_["boiler_room"] = textures_[11];

		SetTexture(textures_[12], (resources_directory_g + std::string("/textures/crew.png")).c_str());
		texture_map_["crew"] = textures_[12];

		SetTexture(textures_[13], (resources_directory_g + std::string("/textures/bullet.png")).c_str());
		texture_map_["bullet"] = textures_[13];

		SetTexture(textures_[14], (resources_directory_g + std::string("/textures/gun.png")).c_str());
		texture_map_["gun"] = textures_[14];

		// workstation_empty
		SetTexture(textures_[15], (resources_directory_g + std::string("/textures/workstation_empty.png")).c_str());
		texture_map_["workstation_empty"] = textures_[15];
		
		// workstation_occupied
		SetTexture(textures_[16], (resources_directory_g + std::string("/textures/workstation_occupied.png")).c_str());
		texture_map_["workstation_occupied"] = textures_[16];

		// collision_square
		SetTexture(textures_[17], (resources_directory_g + std::string("/textures/collision_square.png")).c_str());
		texture_map_["collision_square"] = textures_[17];

		SetTexture(textures_[18], (resources_directory_g + std::string("/textures/big_bullet.png")).c_str());
		texture_map_["big_bullet"] = textures_[18];

		SetTexture(textures_[19], (resources_directory_g + std::string("/textures/close.png")).c_str());
		texture_map_["close"] = textures_[19];

		SetTexture(textures_[20], (resources_directory_g + std::string("/textures/gui/background.png")).c_str());

		
		
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Texture Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	}
	
}