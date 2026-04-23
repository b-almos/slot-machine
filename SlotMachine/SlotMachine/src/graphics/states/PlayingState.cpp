#include "PlayingState.h"

namespace slot::gfx {
	PlayingState::PlayingState(StateManager& sm, const AssetManager& assets, SlotMachine& logic)
		: State{ sm },
		asset_manager{ assets },
		game_logic{ logic },
		background{ assets.getTexture("game_background") },
		hud{ assets },
		reel_set_view{ assets, logic }
	{
		float scale_x = virtual_width / static_cast<float>(background.getTexture().getSize().x);
		float scale_y = virtual_height / static_cast<float>(background.getTexture().getSize().y);
		background.setScale({ scale_x, scale_y });
	}



	void PlayingState::handleEvent(const sf::Event& event) 
	{
		if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
			if (key->code == sf::Keyboard::Key::Space) {
				if (reel_set_view.isSpinning()) {
					reel_set_view.skipAnimation(spin_result.value());
				}
				else if (game_logic.validateBet()) {
					spin_result = game_logic.spin();
					reel_set_view.startSpin();
				}
			}

			if (key->code == sf::Keyboard::Key::Up) {
				if (game_logic.validateRaise())
					game_logic.raiseBetLevel();
			}

			if (key->code == sf::Keyboard::Key::Down) {
				if (game_logic.validateLower())
					game_logic.lowerBetLevel();
			}
		}
	}

	void PlayingState::update(float dt) 
	{
		if (spin_result.has_value())
			reel_set_view.update(dt, spin_result.value());

		int last_win = spin_result.has_value() ? spin_result->total_win : 0;
		hud.update(game_logic.getBalance(), game_logic.getCurrentBet(), last_win);
	}
	void PlayingState::render(sf::RenderWindow& window)
	{
		window.draw(background);
		reel_set_view.render(window);
		hud.draw(window);
	}
}