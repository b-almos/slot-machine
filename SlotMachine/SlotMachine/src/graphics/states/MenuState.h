#pragma once

#include "graphics/states/State.h"
#include "graphics/resources/AssetManager.h"
#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>
#include <graphics/GraphicsTypes.h>
#include <graphics/GraphicsConstants.h>
#include <core/Constants.h>

namespace slot::gfx {
	class MenuState : public State {
	private:
		const AssetManager& asset_manager;
		SlotMachine& game_logic;

		sf::Sprite background;
		sf::Text title_text;
		sf::Text prompt_text;
		
	public:
		MenuState(StateManager& sm, const AssetManager& assets, SlotMachine& logic);

		void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
		void update(float dt) override;
		void render(sf::RenderWindow& window) override;
	};
}