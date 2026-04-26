#pragma once

#include <array>
#include "Constants.h"
#include "Types.h"

namespace slot {
	class Paytable {
	private:
		static constexpr std::array<std::array<int, reels_count>, symbol_count> paytable	// paytable of multipliers based on symbol (rows) and match count (columns)
		{
			{
				{{0, 1, 4, 10, 40}},		// cherry
				{{0, 0, 4, 10, 40}},		// lemon
				{{0, 0, 4, 10, 40}},		// orange
				{{0, 0, 4, 10, 40}},		// plum
				{{0, 0, 8, 20, 80}},		// bell
				{{0, 0, 10, 40, 100}},		// watermelon
				{{0, 0, 10, 40, 100}},		// grapes
				{{0, 0, 20, 200, 1000}}		// seven
			}
		};

	public:
		std::array<int, payline_count> evaluatePaytable(const std::array<PaylineResult, payline_count>&) const;		// returns the multipliers for each payline based on the paytable

		static int totalMultiplier(const std::array<int, payline_count>&);
	};
}