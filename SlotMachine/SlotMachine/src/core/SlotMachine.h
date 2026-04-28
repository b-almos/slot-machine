#pragma once

#include "Reel.h"
#include "ReelSet.h"
#include "Paylines.h"
#include "Paytable.h"
#include "CreditSystem.h"
#include <array>
#include <random>

namespace slot {
	class SlotMachine {
	private:
		ReelSet reel_set;
		Paylines paylines;
		Paytable paytable;
		CreditSystem credit_system;

		std::mt19937 engine;
		std::uniform_int_distribution<int> dist;

		std::array<int, reels_count> generateStopPositions();
	public:
		SlotMachine();

		SpinResult spin();

		void run_game();

		void monte_carlo_simulation();

		const Symbol getSymbolAt(const int reel, const int stop_position, const int offset) const;

		// forward to creditsystem
		int getBalance() const;
		int getCurrentBet() const;

		bool validateRaise() const;
		bool validateLower() const;
		void raiseBetLevel();
		void lowerBetLevel();

		bool validateBet() const;


		void addWinnings(const int total_win);
	};
}