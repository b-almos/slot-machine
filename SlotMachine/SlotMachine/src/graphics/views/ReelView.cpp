#include "graphics/views/ReelView.h"

namespace slot::gfx {
	ReelView::ReelView(int index, const AssetManager& assets, SlotMachine& logic)
		:state{ReelState::Idle},
		scroll_position{ index * 1.f },
		target_stop{ 0 },
		stop_start_position{ 0.f },
		stop_timer{ 0.f },
		reel_index{ index },
		asset_manager{ assets },
		game_logic{ logic }
	{
	}

	void ReelView::snapToResult(int target)
	{
		target_stop = target;
		scroll_position = static_cast<float>(target);
		state = ReelState::Idle;
	}

	void ReelView::startSpin()
	{
		state = ReelState::Spinning;
	}

	void ReelView::startStop(int target)
	{
		target_stop = target;
		state = ReelState::Stopping;
		stop_timer = 0.f;
		stop_start_position = scroll_position;
	}

	void ReelView::update(float dt)
	{
		switch (state) {
		case ReelState::Idle:
			break;
		case ReelState::Spinning:
			scroll_position += spin_speed * dt;
			while (scroll_position >= static_cast<float>(strip_size))
				scroll_position -= static_cast<float>(strip_size);
			break;
		case ReelState::Stopping:
			stop_timer += dt;
			float t = stop_timer / stop_duration;

			if (t >= 1.f) {
				scroll_position = static_cast<float>(target_stop);
				state = ReelState::Idle;
			}
			else {
				float distance = static_cast<float>(target_stop) - stop_start_position;

				while (distance < static_cast<float>(strip_size) / 2.f)
					distance += static_cast<float>(strip_size);

				float eased = easeOutBack(t);
				scroll_position = stop_start_position + distance * eased;

				while (scroll_position >= static_cast<float>(strip_size))
					scroll_position -= static_cast<float>(strip_size);
				while (scroll_position < 0.f)
					scroll_position += static_cast<float>(strip_size);
			}
			break;
		}
	}

	void ReelView::render(sf::RenderWindow& window)
	{
		sf::View view = window.getView();

		float panelLeft = grid_origin_x + reel_index * (symbol_size + reel_gap);
		float panelTop = grid_origin_y;

		// Scissor uses ratios (0 to 1) of the view size
		view.setScissor(sf::FloatRect(
			{ panelLeft / virtual_width, panelTop / virtual_height },
			{ symbol_size / virtual_width, grid_height / virtual_height }
		));
		window.setView(view);

		int base = static_cast<int>(std::floor(scroll_position));
		float fraction = scroll_position - base;

		for (int offset = -2; offset <= 2; ++offset) {
			float y = grid_origin_y + (offset + 1) * symbol_size - fraction * symbol_size;
			float x = grid_origin_x + reel_index * (symbol_size + reel_gap);

			Symbol symbol = game_logic.getSymbolAt(reel_index, base, offset);
			std::string key = symbolToTextureKey(symbol);
			sf::Sprite sprite(asset_manager.getTexture(key));
			float scale = symbol_size / static_cast<float>(asset_manager.getTexture(key).getSize().x);
			sprite.setScale({ scale, scale });
			sprite.setPosition({ x, y });
			window.draw(sprite);
		}

		view.setScissor(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
		window.setView(view);
	}

	bool ReelView::isIdle() const { return state == ReelState::Idle; }

	bool ReelView::isSpinning() const { return state == ReelState::Spinning; }
}