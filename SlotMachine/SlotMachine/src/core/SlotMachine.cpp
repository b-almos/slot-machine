#include "SlotMachine.h"

namespace slot {
	SlotMachine::SlotMachine()
		: reel_set{}, paylines{}, paytable{}, credit_system{}, engine{ std::random_device{}()}, dist(0, strip_size-1)
	{
	}

	std::array<int, reels_count> SlotMachine::generateStopPositions()
	{
		std::array<int, reels_count> stop_positions;

		for (int i = 0; i < reels_count; ++i) {
			stop_positions[i] = dist(engine);
		}

		return stop_positions;
	}

	SpinResult SlotMachine::spin()
	{
		credit_system.subtractBet();

		std::array<int, reels_count> stop_positions = generateStopPositions();
		reel_set.spin(stop_positions);

		std::array<std::array<Symbol, reels_count>, rows_count > grid = reel_set.getGrid();
		std::array<PaylineResult, payline_count> paylines_results = paylines.evaluatePaylines(grid);
		std::array<int, payline_count> paytable_results = paytable.evaluatePaytable(paylines_results);
		int total_multiplier = paytable.totalMultiplier(paytable_results);


		credit_system.addWinnings(total_multiplier);

		return SpinResult{ stop_positions, paylines_results, paytable_results, credit_system.getCurrentBet() * total_multiplier };

	}

	void SlotMachine::run_game()
	{
		while (credit_system.getBalance() != 0) {
			std::cout << "\nbalance: " << credit_system.getBalance() << '\n';

			char choice = ' ';
			while (choice != 'n') {
				std::cout << "current_bet: " << credit_system.getCurrentBet() << '\n'
					<< "want to (r)aise or (l)ower the bet? (press n if (n)ot)\n"
					<< "> ";
				std::cin >> choice;
				switch (choice) {
				case 'r':
					if (credit_system.validateRaise())
						credit_system.raiseBetLevel();
					else
						std::cout << "\ncan't raise more\n";
					break;
				case 'l':
					if (credit_system.validateLower())
						credit_system.lowerBetLevel();
					else
						std::cout << "\ncan't lower more\n";
					break;
				case 'n':
					break;
				}
			}

			if (credit_system.validateBet()) {
				SpinResult spin_result = spin();

				reel_set.print();
				std::cout << "win: " << spin_result.total_win << '\n';
			}

			else {
				std::cout << "\nerror: not enough balance\n";
			}
		}
	}

	void SlotMachine::monte_carlo_simulation()
	{
		credit_system.setBalance(1000000000);
		credit_system.setBet(1);
		long long total_winnings = 0;

		while (credit_system.getBalance() != 0) {
			SpinResult spin_result = spin();
			total_winnings += spin_result.total_win;
		}

		std::cout << total_winnings << '\n';
	}
}