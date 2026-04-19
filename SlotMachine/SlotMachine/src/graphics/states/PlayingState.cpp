#include "PlayingState.h"

namespace slot::gfx {
	PlayingState::PlayingState(const AssetManager& assets, SlotMachine& logic)
		: asset_manager{ assets }, game_logic{ logic }, press_space_to_play{ assets.getFont("main_font"), "PRESS SPACE TO PLAY", 110 }
	{
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
		if (!spin_result.has_value()) {
			window.draw(press_space_to_play);
			return;
		}

		for (int col = 0; col < reels_count; ++col) {
			for (int row = 0; row < rows_count; ++row) {
				Symbol symbol = game_logic.getSymbolAt(col, spin_result->stop_positions[col], row - 1);
				std::string key = symbolToTextureKey(symbol);
				sf::Sprite sprite(asset_manager.getTexture(key));
				sprite.setPosition({ 320.f + col * 128.f, 168.f + row * 128.f });
				window.draw(sprite);
			}
		}
	}
}