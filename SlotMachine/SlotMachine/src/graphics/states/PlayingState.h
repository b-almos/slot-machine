#pragma once

#include "State.h"

namespace slot::gfx {
	class PlayingState : public State {
	public:
		void handleEvent(const sf::Event& event) override;
		void update(float dt) override;
		void render(sf::RenderWindow& window) override;
	};
}