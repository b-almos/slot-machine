#include "ReelSet.h"

namespace slot {
	ReelSet::ReelSet()
		: reels{ Reel(strip_1), Reel(strip_2), Reel(strip_3), Reel(strip_4), Reel(strip_5) }, grid { }
	{
	}

	void ReelSet::spin(const std::array<int, reels_count>& stop_positions)
	{
		for (int i = 0; i < reels_count; ++i) {
			std::array<Symbol, rows_count> showing_symbols = reels[i].getShowingSymbols(stop_positions[i]);
			for (int j = 0; j < rows_count; ++j) {
				grid[j][i] = showing_symbols[j];
			}
		}
	}

	const void ReelSet::print()
	{
		for (int i = 0; i < rows_count; ++i) {
			for (int j = 0; j < reels_count; ++j) {
				std::cout << static_cast<int>(grid[i][j]) << ' ';
			}
			std::cout << '\n';
		}
	}
}