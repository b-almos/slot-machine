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
#include "graphics/views/ReelView.h"
#include "graphics/views/ReelSetView.h"

namespace slot::gfx {
	class PlayingState : public State {
	private:
		const AssetManager& asset_manager;
		SlotMachine& game_logic;
		HUD hud;
		std::optional<SpinResult> spin_result;

		sf::Sprite background;

		ReelSetView reel_set_view;
	public:
		void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
		void update(float dt) override;
		void render(sf::RenderWindow& window) override;

		PlayingState(StateManager& sm, const AssetManager&, SlotMachine&);
	};
}