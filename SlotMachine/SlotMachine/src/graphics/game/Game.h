#pragma once

#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>

namespace slot::gfx {
	class Game {
	private:
		sf::RenderWindow game_window;
		slot::SlotMachine game_logic;

		void processEvents();
		void update(float dt);
		void render();

	public:
		Game();
		void run();
	};
}