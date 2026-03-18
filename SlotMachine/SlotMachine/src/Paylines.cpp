#include "Paylines.h"

namespace slot {
	const std::array<PaylineResult, payline_count> Paylines::evaluatePaylines(const std::array<std::array<Symbol, reels_count>, rows_count>& grid)
	{
		std::array<PaylineResult, payline_count> payline_results;

		for (int i = 0; i < payline_count; ++i) {
			payline_results[i].symbol = grid[paylines[i][0]][0];

			payline_results[i].match_count = 1;
			for (int j = 1; j < reels_count; ++j) {
				if (payline_results[i].symbol == grid[paylines[i][j]][j])
					++payline_results[i].match_count;
				else
					break;
			}
		}

		return payline_results;
	}
}