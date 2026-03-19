#pragma once

#include "Constants.h"
#include <array>

namespace slot {
	class CreditSystem {
	private:
		int balance;
		static constexpr std::array<int, bet_levels_count> bet_levels
		{
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
		};
		int bet_level_position;

	public:
		CreditSystem();

		bool validateRaise() const;
		bool validateLower() const;
		void raiseBetLevel();
		void lowerBetLevel();

		bool validateBet() const;
		void subtractBet();
		void addWinnings(const int);

		int getBalance() const;
		int getCurrentBet() const;
	};
}