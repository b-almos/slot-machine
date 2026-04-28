#include "CreditSystem.h"

namespace slot {
	CreditSystem::CreditSystem()
		: balance{ default_balance }, bet_level_position{ starting_bet_level_position } {}

	void CreditSystem::setBalance(const int new_balance)
	{
		balance = new_balance;
	}

	void CreditSystem::setBet(const int new_bet)
	{
		for (int i = 0; i < bet_levels.size(); ++i) {
			if (new_bet == bet_levels[i]) {
				bet_level_position = i;
				return;
			}
		}
	}

	bool CreditSystem::validateRaise() const
	{
		if (bet_level_position == bet_levels_count - 1)		// had to subtract 1 because of the bet_levels array indicing starting from 0
			return false;
		return true;
	}


	bool CreditSystem::validateLower() const
	{
		if (bet_level_position == 0)		// lowest index of the bet_levels array
			return false;
		return true;
	}

	void CreditSystem::raiseBetLevel()
	{
		++bet_level_position;
	}

	void CreditSystem::lowerBetLevel()
	{
		--bet_level_position;
	}

	bool CreditSystem::validateBet() const
	{
		if (balance - bet_levels[bet_level_position] < 0)		// if not enough balance for a bet
			return false;
		return true;
	}

	void CreditSystem::subtractBet()
	{
		balance -= bet_levels[bet_level_position];
	}

	void CreditSystem::addWinnings(const int total_win)
	{
		balance += total_win;
	}

	int CreditSystem::getBalance() const
	{
		return balance;
	}

	int CreditSystem::getCurrentBet() const
	{
		return bet_levels[bet_level_position];
	}
}