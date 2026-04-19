#include "PlayingState.h"

namespace slot::gfx {
	void PlayingState::handleEvent(const sf::Event& event) {}
	void PlayingState::update(float dt) {}
	void PlayingState::render(sf::RenderWindow& window)
	{
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);

		window.draw(shape);
	}
}