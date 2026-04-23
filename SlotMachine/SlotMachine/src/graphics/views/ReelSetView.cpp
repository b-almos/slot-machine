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
}