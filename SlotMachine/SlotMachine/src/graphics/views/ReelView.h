#pragma once

#include "graphics/GraphicsTypes.h"
#include "graphics/resources/AssetManager.h"
#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>
#include "graphics/GraphicsConstants.h"
#include "graphics/Easing.h"

namespace slot::gfx {
	class ReelView {
	private:
		ReelState state;
		float scroll_position;
		int target_stop;
		float stop_start_position;
		float stop_timer;
		int reel_index;
		const AssetManager& asset_manager;
		SlotMachine& game_logic;

	public:
		ReelView(int index, const AssetManager& assets, SlotMachine& logic);
		
		void snapToResult(int target);
		void startSpin();
		void startStop(int target);
		void update(float dt);

		void render(sf::RenderWindow& window);

		bool isIdle() const;
		bool isSpinning() const;
	};
}