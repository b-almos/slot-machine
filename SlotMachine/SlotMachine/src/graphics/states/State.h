#pragma once

#include <SFML/Graphics.hpp>

namespace slot::gfx {
	class StateManager;

	class State {
	protected:
		StateManager& state_manager;
	public:
		State(StateManager& sm);

		virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
		virtual void update(float dt) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual void onEnter() {}
		virtual void onExit() {}
		virtual ~State() = default;
	};
}