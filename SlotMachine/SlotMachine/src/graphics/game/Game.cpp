#include "Game.h"

namespace slot::gfx {
	Game::Game()
		: game_window(sf::VideoMode({ 1280u, 720u }), "Slot Game"), game_logic{}
	{
	}

	void Game::processEvents()
	{
		while (const std::optional event = game_window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				game_window.close();
		}
	}

	void Game::update(float dt)
	{

	}

	void Game::render()
	{
		game_window.clear(sf::Color::Magenta);
		game_window.display();
	}

	void Game::run()
	{
		sf::Clock clock;
		while (game_window.isOpen()) {
			float dt = clock.restart().asSeconds();
			processEvents();
			update(dt);
			render();
		}
	}
}