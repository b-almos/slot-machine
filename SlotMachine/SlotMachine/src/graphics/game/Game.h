#pragma once

#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>
#include "graphics/states/StateManager.h"
#include "graphics/states/MenuState.h"
#include "graphics/resources/AssetManager.h"
#include "graphics/GraphicsConstants.h"

namespace slot::gfx {
	class Game {
	private:
		sf::RenderWindow game_window;
		slot::SlotMachine game_logic;
		AssetManager asset_manager;
		StateManager state_manager;

		void processEvents();
		void update(float dt);
		void render();

	public:
		Game();
		void run();
	};
}