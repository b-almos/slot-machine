#pragma once

#include "Constants.h"
#include "Types.h"
#include <array>

namespace slot {
	class Paylines {
	private:
		static constexpr std::array<std::array<int, reels_count>, payline_count> paylines
		{	
			{
				{{0, 0, 0, 0, 0}},		// top line
				{{1, 1, 1, 1, 1}},		// middle line
				{{2, 2, 2, 2, 2}},		// bottom line
				{{2, 1, 0, 1, 2}},		// inverted v line
				{{0, 1, 2, 1, 0}}		// v line
			}
		};

	public:
		std::array<PaylineResult, payline_count> evaluatePaylines(const std::array<std::array<Symbol, reels_count>, rows_count>&) const;
	};
}