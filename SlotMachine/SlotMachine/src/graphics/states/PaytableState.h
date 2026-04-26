#pragma once

#include "State.h"
#include "graphics/resources/AssetManager.h"
#include "core/SlotMachine.h"
#include "graphics/GraphicsConstants.h"
#include "core/Constants.h"
#include "graphics/GraphicsTypes.h"
#include <SFML/Graphics.hpp>

namespace slot::gfx {
	class PaytableState : public State {
	private:
		const AssetManager& asset_manager;
		SlotMachine& game_logic;
		sf::RectangleShape overlay;
		sf::Text title_text;
		sf::Text prompt_text;

	public:
		PaytableState(StateManager& sm, const AssetManager& assets, SlotMachine& logic);

		void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
		void update(float dt) override;
		void render(sf::RenderWindow& window) override;
	};
}