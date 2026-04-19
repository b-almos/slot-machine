#pragma once

#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>
#include "graphics/states/StateManager.h"
#include "graphics/states/PlayingState.h"

namespace slot::gfx {
	class Game {
	private:
		sf::RenderWindow game_window;
		slot::SlotMachine game_logic;
		StateManager state_manager;

		void processEvents();
		void update(float dt);
		void render();

	public:
		Game();
		void run();
	};
}