#include "graphics/states/MenuState.h"
#include "graphics/states/PlayingState.h"
#include "graphics/states/StateManager.h"

namespace slot::gfx {
	MenuState::MenuState(StateManager& sm, const AssetManager& assets, SlotMachine& logic)
		: State{ sm },
		asset_manager{ assets },
		game_logic{ logic },
		background{ assets.getTexture("game_background") },
		title_text{ assets.getFont("main_font"), "SLOT MACHINE", 110 },
		prompt_text{ assets.getFont("main_font"), "PRESS SPACE TO PLAY", 90, }
	{
		float scale_x = virtual_width / static_cast<float>(background.getTexture().getSize().x);
		float scale_y = virtual_height / static_cast<float>(background.getTexture().getSize().y);
		background.setScale({ scale_x, scale_y });

		title_text.setFillColor(sf::Color(255, 225, 100));
		title_text.setPosition({
			(virtual_width - title_text.getLocalBounds().size.x) / 2.f,
			menu_title_text_y
			});

		prompt_text.setFillColor(sf::Color(180, 150, 50));
		prompt_text.setPosition({
			(virtual_width - prompt_text.getLocalBounds().size.x) / 2.f,
			menu_prompt_text_y
			});
	}

	void MenuState::handleEvent(const sf::Event& event, sf::RenderWindow& window)
	{
		if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
			if (key->code == sf::Keyboard::Key::Space) {
				state_manager.replaceState(std::make_unique<PlayingState>(state_manager, asset_manager, game_logic));
			}
		}
	}

	void MenuState::update(float dt) {}

	void MenuState::render(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(title_text);
		window.draw(prompt_text);
	}
}