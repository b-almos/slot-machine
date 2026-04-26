#pragma once

#include <array>
#include "Constants.h"

namespace slot {
	enum class Symbol {
		Cherry,
		Lemon,
		Orange,
		Plum,
		Bell,
		Watermelon,
		Grapes,
		Seven
	};

	struct PaylineResult {
		Symbol symbol;
		int match_count;
	};

	struct SpinResult {
		std::array<int, reels_count> stop_positions;
		std::array<PaylineResult, payline_count> paylines_results;
		std::array<int, payline_count> paytable_result;
		int total_win;
	};
}