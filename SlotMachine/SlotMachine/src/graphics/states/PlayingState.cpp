#include "PlayingState.h"

namespace slot::gfx {
	PlayingState::PlayingState(const AssetManager& assets, SlotMachine& logic)
		: asset_manager{ assets }, 
		game_logic{ logic }, 
		press_space_to_play{ assets.getFont("main_font"), "PRESS SPACE TO PLAY", 110, },
		background{ assets.getTexture("game_background") }
	{
		float scale_x = virtual_width / static_cast<float>(background.getTexture().getSize().x);
		float scale_y = virtual_height / static_cast<float>(background.getTexture().getSize().y);
		background.setScale({ scale_x, scale_y });

		for (int i = 0; i < 5; ++i)
		{
			reel_panels[i].setSize({ symbol_size, grid_height });
			reel_panels[i].setPosition({
				grid_origin_x + i * (symbol_size + reel_gap),
				grid_origin_y
				});
			reel_panels[i].setFillColor(sf::Color(40, 20, 60));			// darker purple than the background
			reel_panels[i].setOutlineColor(sf::Color(218, 165, 32));	// nice gold
			reel_panels[i].setOutlineThickness(2.f);
		}
	}



	void PlayingState::handleEvent(const sf::Event& event) 
	{
		if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
			if (key->code == sf::Keyboard::Key::Space) {
				spin_result = game_logic.spin();
			}
		}
	}

	void PlayingState::update(float dt) {}
	void PlayingState::render(sf::RenderWindow& window)
	{
		window.draw(background);

		if (!spin_result.has_value()) {
			window.draw(press_space_to_play);
			return;
		}

		for (const auto& panel : reel_panels)
			window.draw(panel);

		for (int col = 0; col < reels_count; ++col) {
			for (int row = 0; row < rows_count; ++row) {
				Symbol symbol = game_logic.getSymbolAt(col, spin_result->stop_positions[col], row - 1);
				std::string key = symbolToTextureKey(symbol);
				sf::Sprite sprite(asset_manager.getTexture(key));
				float scale = symbol_size / static_cast<float>(asset_manager.getTexture(key).getSize().x);
				sprite.setScale({ scale, scale });
				sprite.setPosition({
					grid_origin_x + col * (symbol_size + reel_gap),
					grid_origin_y + row * symbol_size
					
				});
				window.draw(sprite);
			}
		}
	}
}