#include "Game.h"

namespace slot::gfx {
	Game::Game()
		: game_window(sf::VideoMode({ 1280u, 720u }), "Slot Game"), game_logic{}, state_manager{}
	{
		state_manager.pushState(std::make_unique<PlayingState>());
		state_manager.applyPendingChange();
	}

	void Game::processEvents()
	{
		while (const std::optional event = game_window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				game_window.close();

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