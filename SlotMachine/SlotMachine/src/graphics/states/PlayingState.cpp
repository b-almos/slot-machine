#include "PlayingState.h"

namespace slot::gfx {
	PlayingState::PlayingState(const AssetManager& assets, SlotMachine& logic)
		: asset_manager{ assets }, 
		game_logic{ logic }, 
		press_space_to_play{ assets.getFont("main_font"), "PRESS SPACE TO PLAY", 110, },
		background{ assets.getTexture("game_background") },
		hud{ assets }
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
			reel_panels[i].setFillColor(sf::Color(30, 5, 10));
			reel_panels[i].setOutlineColor(sf::Color(218, 165, 32));
			reel_panels[i].setOutlineThickness(2.f);
		}

		for (int i = 0; i < 5; ++i)
			reel_views[i] = std::make_unique<ReelView>(i, asset_manager, game_logic);
	}



	void PlayingState::handleEvent(const sf::Event& event) 
	{
		if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
			/*if (key->code == sf::Keyboard::Key::Space) {
				if (game_logic.validateBet())
					spin_result = game_logic.spin();
			}*/

			if (key->code == sf::Keyboard::Key::Space) {
				if (!is_spinning && game_logic.validateBet()) {
					spin_result = game_logic.spin();
					for (int i = 0; i < 5; ++i)
						reel_views[i]->startSpin();
					is_spinning = true;
					spin_timer = 0.f;
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
		int last_win = spin_result.has_value() ? spin_result->total_win : 0;
		hud.update(game_logic.getBalance(), game_logic.getCurrentBet(), last_win);

		if (is_spinning) {
			spin_timer += dt;

			for (int i = 0; i < 5; ++i) {
				float stop_time = spin_base_time + i * reel_stagger;
				if (spin_timer >= stop_time && reel_views[i]->isSpinning())
					reel_views[i]->startStop(spin_result->stop_positions[i]);

				if (is_spinning) {
					bool all_idle = true;
					for (int i = 0; i < 5; ++i) {
						if (!reel_views[i]->isIdle())
							all_idle = false;
					}
					if (all_idle)
						is_spinning = false;
				}
			}
		}

		for (int i = 0; i < 5; ++i)
			reel_views[i]->update(dt);
		
	}
	void PlayingState::render(sf::RenderWindow& window)
	{
		window.draw(background);

		if (!spin_result.has_value()) {
			window.draw(press_space_to_play);
			return;
		}

		for (const auto& panel : reel_panels)
			window.draw(panel);

		/*for (int col = 0; col < reels_count; ++col) {
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
		}*/

		for (int i = 0; i < 5; ++i) {
			reel_views[i]->render(window);
			hud.draw(window);
		}
	}
}