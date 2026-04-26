#pragma once

#include <vector>
#include "State.h"
#include "graphics/GraphicsTypes.h"

namespace slot::gfx {
	class StateManager {
	private:
		std::vector<std::unique_ptr<State>> states;
		PendingAction pending_action;
		std::unique_ptr<State> pending_state;
	public:
		void pushState(std::unique_ptr<State>);
		void popState();
		void replaceState(std::unique_ptr<State>);
		void handleEvent(const sf::Event& event, sf::RenderWindow& window);
		void update(float);
		void render(sf::RenderWindow&);
		void applyPendingChange();

		StateManager();
	};
}