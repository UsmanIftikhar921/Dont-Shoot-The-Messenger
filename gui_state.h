#ifndef GUI_STATE_H_
#define GUI_STATE_H_

#include <vector>

namespace game {
    enum Segment {
        UNASSIGNED,
        BOW,
        BOILER,
        STERN_GUNS,
        PORT_GUNS,
        STARBOARD_GUNS,
        PORT_ENGINE,
        STARBOARD_ENGINE,
    };

    struct CrewData {
        float health;
        Segment assigned_segment;
        bool alive;
    };

    struct FireSelector {
        bool port;
        bool starboard;
        bool stern;
    };
	class GuiState {

	public:
        GuiState();

        // Getters & Setters
        std::vector<CrewData> GetCrewDataVec() { return crew_data_vec_; }
        void SetCrewData(int index, CrewData crew_data) { crew_data_vec_[index] = crew_data; }
        void SetCrewDataVec(std::vector<CrewData> crew_data_vec) { crew_data_vec_ = crew_data_vec; }

        float GetSteamPressure() { return steam_pressure_; }
        void SetSteamPressure(float steam_pressure) { steam_pressure_ = steam_pressure; }

        int GetPortEnginePower() { return port_engine_power_; }
        void SetPortEnginePower(int port_engine_power) { port_engine_power_ = port_engine_power; }

        int GetStarboardEnginePower() { return starboard_engine_power_; }
        void SetStarboardEnginePower(int starboard_engine_power) { starboard_engine_power_ = starboard_engine_power; }

        FireSelector GetFireSelector() { return fire_selector_; }
        void SetFireSelector(FireSelector fire_selector) { fire_selector_ = fire_selector; }

    protected:
        std::vector<CrewData> crew_data_vec_; // Holds list of CrewData structs
        float steam_pressure_;
        int port_engine_power_; // Can be -3, -2, -1, 0, 1, 2, 3
        int starboard_engine_power_; // Can be -3, -2, -1, 0, 1, 2, 3
        FireSelector fire_selector_;
	};
}

#endif