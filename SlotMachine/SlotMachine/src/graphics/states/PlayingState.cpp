#include "PlayingState.h"
#include "PaytableState.h"
#include "StateManager.h"

namespace slot::gfx {
	PlayingState::PlayingState(StateManager& sm, const AssetManager& assets, SlotMachine& logic)
		: State{ sm },
		asset_manager{ assets },
		game_logic{ logic },
		background{ assets.getTexture("game_background") },
		hud{ assets },
		reel_set_view{ assets, logic },
		displayed_balance{ 0 },
		last_win{ 0 },
		counting_up{ false },
		was_spinning{ false },
		count_rate{ 0.f },
		count_accumulator{ 0.f }
	{
		float scale_x = virtual_width / static_cast<float>(background.getTexture().getSize().x);
		float scale_y = virtual_height / static_cast<float>(background.getTexture().getSize().y);
		background.setScale({ scale_x, scale_y });

		displayed_balance = game_logic.getBalance();
	}



	void PlayingState::handleEvent(const sf::Event& event, sf::RenderWindow& window)
	{
		if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
			if (key->code == sf::Keyboard::Key::Space) {
				if (reel_set_view.isSpinning()) {
					reel_set_view.skipAnimation(spin_result.value());
				}
				else if (counting_up) {
					displayed_balance = game_logic.getBalance();
					counting_up = false;
				}
				else if (game_logic.validateBet()) {
					spin_result = game_logic.spin();
					displayed_balance = game_logic.getBalance();
					reel_set_view.startSpin();
				}
			}

			if (key->code == sf::Keyboard::Key::Up) {
				if (!counting_up && !reel_set_view.isSpinning())
					if (game_logic.validateRaise())
						game_logic.raiseBetLevel();
			}

			if (key->code == sf::Keyboard::Key::Down) {
				if (!counting_up && !reel_set_view.isSpinning())
					if (game_logic.validateLower())
						game_logic.lowerBetLevel();
			}

			if (key->code == sf::Keyboard::Key::Tab) {
				if (!reel_set_view.isSpinning()) {
					state_manager.pushState(
						std::make_unique<PaytableState>(state_manager, asset_manager, game_logic)
					);
				}
			}
		}

		if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mouse->button == sf::Mouse::Button::Left) {
				sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse->position);

				if (hud.isSpinClicked(mouse_pos)) {
					if (reel_set_view.isSpinning())
						reel_set_view.skipAnimation(spin_result.value());
					else if (counting_up) {
						displayed_balance = game_logic.getBalance();
						counting_up = false;
					}
					else if (game_logic.validateBet()) {
						spin_result = game_logic.spin();
						displayed_balance = game_logic.getBalance();
						reel_set_view.startSpin();
					}
				}

				if (hud.isBetUpClicked(mouse_pos)) {
					if (!counting_up && !reel_set_view.isSpinning())
						if (game_logic.validateRaise())
							game_logic.raiseBetLevel();
				}

				if (hud.isBetDownClicked(mouse_pos)) {
					if (!counting_up && !reel_set_view.isSpinning())
						if (game_logic.validateLower())
							game_logic.lowerBetLevel();
				}
			}
		}
	}

	void PlayingState::update(float dt) 
	{
		if (spin_result.has_value())
			reel_set_view.update(dt, spin_result.value());

		bool currently_spinning = reel_set_view.isSpinning();
		if (was_spinning && !currently_spinning) {
			last_win = spin_result->total_win;
			displayed_balance = game_logic.getBalance();

			if (last_win > 0) {
				game_logic.addWinnings(last_win);
				count_rate = static_cast<float>(last_win) / balance_count_duration;
				count_accumulator = 0.f;
				counting_up = true;
			}
		}
		was_spinning = currently_spinning;

		if (counting_up) {
			count_accumulator += count_rate * dt;
			int credits_to_add = static_cast<int>(count_accumulator);

			if (credits_to_add > 0) {
				displayed_balance += credits_to_add;
				count_accumulator -= static_cast<float>(credits_to_add);
			}

			if (displayed_balance >= game_logic.getBalance()) {
				displayed_balance = game_logic.getBalance();
				counting_up = false;
				count_accumulator = 0.f;
			}
		}

		hud.update(displayed_balance, game_logic.getCurrentBet(), last_win);

		if (reel_set_view.isSpinning())
			hud.setSpinButtonTexture(asset_manager.getTexture("stop_button"), stop_button_scale_fix);
		else
			hud.setSpinButtonTexture(asset_manager.getTexture("spin_button"), 1.f);
	}

	void PlayingState::render(sf::RenderWindow& window)
	{
		window.draw(background);
		reel_set_view.render(window);

		if (spin_result.has_value() && !reel_set_view.isSpinning() && spin_result->total_win > 0)
			reel_set_view.drawWinLines(window, spin_result.value());

		hud.draw(window);
	}
}