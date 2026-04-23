#pragma once

#include "graphics/views/ReelView.h"

namespace slot::gfx {
	class ReelSetView {
	private:
		std::array<std::unique_ptr<ReelView>, 5> reel_views;
		std::array<sf::RectangleShape, 5> reel_panels;
		float spin_timer;
		bool spinning;
	public:
		ReelSetView(const AssetManager& assets, SlotMachine& logic);

		void startSpin();
		void skipAnimation(const SpinResult& result);
		void update(float dt, const SpinResult& result);
		void render(sf::RenderWindow& window);
		bool isSpinning() const;
	};
}