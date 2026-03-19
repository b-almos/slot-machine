#pragma once

#include <array>
#include "Constants.h"

namespace slot {
	enum class Symbol {
		Cherry,
		Lemon,
		Orange,
		Plum,
		Watermelon,
		Grapes,
		Bell,
		Seven
	};

	struct PaylineResult {
		Symbol symbol;
		int match_count;
	};

	struct SpinResult {
		std::array<std::array<Symbol, reels_count>, rows_count> grid;
		std::array<PaylineResult, payline_count> paylines_results;
		std::array<int, payline_count> paytable_result;
		int total_win;
	};
}