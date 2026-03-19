#include "Paylines.h"

namespace slot {
	std::array<PaylineResult, payline_count> Paylines::evaluatePaylines(const std::array<std::array<Symbol, reels_count>, rows_count>& grid) const
	{
		std::array<PaylineResult, payline_count> paylines_results;

		for (int i = 0; i < payline_count; ++i) {
			paylines_results[i].symbol = grid[paylines[i][0]][0];

			paylines_results[i].match_count = 1;
			for (int j = 1; j < reels_count; ++j) {
				if (paylines_results[i].symbol == grid[paylines[i][j]][j])
					++paylines_results[i].match_count;
				else
					break;
			}
		}

		return paylines_results;
	}
}