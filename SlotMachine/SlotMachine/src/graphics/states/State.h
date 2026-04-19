#pragma once

#include <SFML/Graphics.hpp>

namespace slot::gfx {
	class State {
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float dt) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual void onEnter() {}
		virtual void onExit() {}
		virtual ~State() = default;
	};
}