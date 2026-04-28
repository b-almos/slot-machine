#include "ReelSetView.h"

namespace slot::gfx {
	ReelSetView::ReelSetView(const AssetManager& assets, SlotMachine& logic)
		: spin_timer{ 0.f }, spinning{ false }
	{
		for (int i = 0; i < reels_count; ++i) {
			reel_views[i] = std::make_unique<ReelView>(i, assets, logic);
		}

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
	}

	void ReelSetView::startSpin()
	{
		for (int i = 0; i < reels_count; ++i)
			reel_views[i]->startSpin();
		spinning = true;
		spin_timer = 0.f;
	}

	void ReelSetView::skipAnimation(const SpinResult& result)
	{
		for (int i = 0; i < reels_count; ++i)
			reel_views[i]->snapToResult(result.stop_positions[i]);
		spinning = false;
	}

	void ReelSetView::update(float dt, const SpinResult& result)
	{
		if (spinning) {
			spin_timer += dt;

			for (int i = 0; i < reels_count; ++i) {
				float stop_time = spin_base_time + i * reel_stagger;
				
				if (spin_timer >= stop_time && reel_views[i]->isSpinning())
					reel_views[i]->startStop(result.stop_positions[i]);
			}

			bool all_idle = true;
			for (int i = 0; i < reels_count; ++i) {
				if (!reel_views[i]->isIdle())
					all_idle = false;
			}
			if (all_idle)
				spinning = false;
		}

		for (int i = 0; i < reels_count; ++i)
			reel_views[i]->update(dt);
	}

	void ReelSetView::render(sf::RenderWindow& window)
	{
		for (const auto& panel : reel_panels)
			window.draw(panel);

		for (int i = 0; i < reels_count; ++i)
			reel_views[i]->render(window);
	}

	bool ReelSetView::isSpinning() const
	{
		return spinning;
	}

	void ReelSetView::drawWinLines(sf::RenderWindow& window, const SpinResult& result)
	{
		const auto& payline_defs = Paylines::getPaylines();

		for (int line = 0; line < payline_count; ++line)
		{
			if (result.paytable_result[line] == 0)
				continue;

			sf::Color color = payline_colors[line];
			int match_count = result.paylines_results[line].match_count;

			std::array<sf::Vector2f, reels_count> centers;
			for (int reel = 0; reel < reels_count; ++reel)
			{
				int row = payline_defs[line][reel];
				centers[reel] = {
					grid_origin_x + reel * (symbol_size + reel_gap) + symbol_size / 2.f,
					grid_origin_y + row * symbol_size + symbol_size / 2.f
				};
			}

			for (int reel = 0; reel < reels_count - 1; ++reel)
			{
				sf::Vector2f diff = centers[reel + 1] - centers[reel];
				float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
				float angle = std::atan2(diff.y, diff.x) * 180.f / 3.14159f;

				sf::RectangleShape segment;
				segment.setSize({ length, win_line_thickness });
				segment.setPosition(centers[reel]);
				segment.setFillColor(color);
				segment.setOrigin({ 0.f, win_line_thickness / 2.f });
				segment.setRotation(sf::degrees(angle));
				window.draw(segment);
			}

			for (int reel = 0; reel < match_count; ++reel)
			{
				int row = payline_defs[line][reel];
				sf::RectangleShape rect;
				rect.setSize({ symbol_size, symbol_size });
				rect.setPosition({
					grid_origin_x + reel * (symbol_size + reel_gap),
					grid_origin_y + row * symbol_size
					});
				rect.setFillColor(sf::Color(color.r, color.g, color.b, 40));
				rect.setOutlineColor(color);
				rect.setOutlineThickness(win_rect_thickness);
				window.draw(rect);
			}
		}
	}
}