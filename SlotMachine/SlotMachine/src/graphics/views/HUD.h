#pragma once

#include <SFML/Graphics.hpp>
#include "graphics/resources/AssetManager.h"
#include "graphics/GraphicsConstants.h"

namespace slot::gfx {
	class HUD {
	private:
		sf::Text balance_label;
		sf::Text balance_value;
		sf::Text bet_label;
		sf::Text bet_value;
		sf::Text win_label;
		sf::Text win_value;

	public:
		HUD(const AssetManager&);

		void update(int balance, int current_bet, int last_win);
		void draw(sf::RenderWindow& window);
	};
}