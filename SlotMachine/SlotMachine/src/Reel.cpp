#include "Reel.h"

namespace slot {
	Reel::Reel()
		: strip{} { }
	Reel::Reel(std::array<Symbol, strip_size> reel_strip)
		: strip{ reel_strip } { }

	const std::array<Symbol, rows_count> Reel::getShowingSymbols(const int stop_position)
	{
		std::array<Symbol, rows_count> showing_symbols;

		// top symbol on a line
		showing_symbols[0] = (strip[(stop_position - 1 + strip.size()) % strip.size()]);

		// middle symbol on a line
		showing_symbols[1] = (strip[stop_position % strip.size()]);

		// bottom position on a line
		showing_symbols[2] = (strip[(stop_position + 1) % strip.size()]);


		return showing_symbols;
	}

	// for the graphical phase
	const Symbol Reel::getSymbolAt(const int stop_position, const int offset)
	{
		int symbol_pos = stop_position + offset;
		while (symbol_pos < 0) {
			symbol_pos += strip.size();
		}
		
		return strip[symbol_pos % strip.size()];
	}
}