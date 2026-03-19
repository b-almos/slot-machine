#include "Paytable.h"

namespace slot {
	std::array<int, payline_count> Paytable::evaluatePaytable(const std::array<PaylineResult, payline_count>& paylines_results) const
	{
		std::array<int, payline_count> paytable_results;

		for (int i = 0; i < payline_count; ++i) {
			paytable_results[i] = paytable[static_cast<int>(paylines_results[i].symbol)][paylines_results[i].match_count-1];	// have to subtract 1 because the array index starts from 0, and match count is always at least 1 (there's always at least one symbol)
		}

		return paytable_results;
	}

	int Paytable::totalWin(const std::array<int, payline_count>& paytable_results)
	{
		int sum = 0;
		for (int i = 0; i < payline_count; ++i) {
			sum += paytable_results[i];
		}

		return sum;
	}
}