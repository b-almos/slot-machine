#include "StateManager.h"

namespace slot::gfx {
	StateManager::StateManager()
		: pending_action{ PendingAction::None } {}

	void StateManager::pushState(std::unique_ptr<State> new_state)
	{
		pending_action = PendingAction::Push;
		pending_state = std::move(new_state);
	}

	void StateManager::popState()
	{
		pending_action = PendingAction::Pop;
	}

	void StateManager::replaceState(std::unique_ptr<State> new_state)
	{
		pending_action = PendingAction::Replace;
		pending_state = std::move(new_state);
	}

	void StateManager::applyPendingChange()
	{
		switch (pending_action) {
		case PendingAction::None:
			break;
		case PendingAction::Push:
			if (!states.empty())
				states.back()->onExit();
			states.push_back(std::move(pending_state));
			states.back()->onEnter();
			break;
		case PendingAction::Pop:
			if (states.empty()) break;
			states.back()->onExit();
			states.pop_back();
			if (!states.empty())
				states.back()->onEnter();
			break;
		case PendingAction::Replace:
			if (states.empty()) break;
			states.back()->onExit();
			states.pop_back();
			states.push_back(std::move(pending_state));
			states.back()->onEnter();
			break;
		}

		pending_action = PendingAction::None;
		pending_state = nullptr;
	}

	void StateManager::handleEvent(const sf::Event& event)
	{
		if (!states.empty())
			states.back()->handleEvent(event);
	}

	void StateManager::update(float dt)
	{
		if (!states.empty())
			states.back()->update(dt);
	}

	void StateManager::render(sf::RenderWindow& window)
	{
		for (const auto& state : states)
			state->render(window);
	}

}