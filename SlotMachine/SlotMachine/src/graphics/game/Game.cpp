#include "Game.h"

namespace slot::gfx {
	Game::Game()
		: game_window(sf::VideoMode::getDesktopMode(), "Slot Game", sf::Style::Default, sf::State::Fullscreen), game_logic{}, state_manager{}
	{
		sf::View view(sf::FloatRect({ 0.f, 0.f }, { virtual_width, virtual_height }));
		game_window.setView(view);
		asset_manager.loadTexture("cherry", "assets/textures/cherry.png");
		asset_manager.loadTexture("lemon", "assets/textures/lemon.png");
		asset_manager.loadTexture("orange", "assets/textures/orange.png");
		asset_manager.loadTexture("plum", "assets/textures/plum.png");
		asset_manager.loadTexture("watermelon", "assets/textures/watermelon.png");
		asset_manager.loadTexture("grape", "assets/textures/grape.png");
		asset_manager.loadTexture("bell", "assets/textures/bell.png");
		asset_manager.loadTexture("seven", "assets/textures/seven.png");
		asset_manager.loadTexture("game_background", "assets/textures/game_background.png");
		asset_manager.loadFont("main_font", "assets/fonts/Roboto-Regular.ttf");
		state_manager.pushState(std::make_unique<PlayingState>(asset_manager, game_logic));
		state_manager.applyPendingChange();
	}

	void Game::processEvents()
	{
		while (const std::optional event = game_window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				game_window.close();

			if (const auto* key = event->getIf<sf::Event::KeyPressed>())
			{
				if (key->code == sf::Keyboard::Key::Escape)
					game_window.close();
			}

			state_manager.handleEvent(*event);
		}
	}

	void Game::update(float dt)
	{
		state_manager.update(dt);
	}

	void Game::render()
	{
		game_window.clear(sf::Color::Black);
		state_manager.render(game_window);
		game_window.display();
	}

	void Game::run()
	{
		sf::Clock clock;
		while (game_window.isOpen()) {
			float dt = clock.restart().asSeconds();
			processEvents();
			update(dt);
			state_manager.applyPendingChange();
			render();
		}
	}
}