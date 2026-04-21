#pragma once

#include "State.h"
#include "graphics/resources/AssetManager.h"
#include "core/SlotMachine.h"
#include <SFML/Graphics.hpp>
#include <graphics/GraphicsTypes.h>
#include <graphics/GraphicsConstants.h>
#include <core/Constants.h>
#include <string>
#include "graphics/views/HUD.h"

namespace slot::gfx {
	class PlayingState : public State {
	private:
		const AssetManager& asset_manager;
		SlotMachine& game_logic;
		HUD hud;
		std::optional<SpinResult> spin_result;

		sf::Text press_space_to_play;
		sf::Sprite background;
		std::array<sf::RectangleShape, 5> reel_panels;
	public:
		void handleEvent(const sf::Event& event) override;
		void update(float dt) override;
		void render(sf::RenderWindow& window) override;

		PlayingState(const AssetManager&, SlotMachine&);
	};
}