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
				{{0, 0, 0, 0, 0}},
				{{1, 1, 1, 1, 1}},
				{{2, 2, 2, 2, 2}},
				{{2, 1, 0, 1, 2}},
				{{0, 1, 2, 1, 0}}
			}
		};

		/*
		static constexpr std::array<int, payline_count> line_1{ 0, 0, 0, 0, 0 };	// top line
		static constexpr std::array<int, payline_count> line_2{ 1, 1, 1, 1, 1 };	// middle line
		static constexpr std::array<int, payline_count> line_3{ 2, 2, 2, 2, 2 };	// bottom line
		static constexpr std::array<int, payline_count> line_4{ 2, 1, 0, 1, 2 };	// inverted v line
		static constexpr std::array<int, payline_count> line_5{ 0, 1, 2, 1, 0 };	// v line
		*/
	public:
		std::array<PaylineResult, payline_count> evaluatePaylines(const std::array<std::array<Symbol, reels_count>, rows_count>&) const;
	};
}