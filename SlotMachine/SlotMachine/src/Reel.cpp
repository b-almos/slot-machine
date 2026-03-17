#include "Reel.h"
#include "Constants.h"

namespace slot {
	Reel::Reel(std::vector<Symbol> reel_strip)
		: strip{ std::move(reel_strip)} { }

	std::vector<Symbol> Reel::getShowingSymbols(const int stop_position)
	{
		std::vector<Symbol> showing_symbols;

		// top symbol on a line
		showing_symbols.push_back(strip[(stop_position - 1 + strip.size()) % strip.size()]);

		// middle symbol on a line
		showing_symbols.push_back(strip[stop_position % strip.size()]);

		// bottom position on a line
		showing_symbols.push_back(strip[(stop_position + 1) % strip.size()]);


		return showing_symbols;
	}

	// for the graphical phase
	Symbol Reel::getSymbolAt(const int stop_position, const int offset)
	{
		int symbol_pos = stop_position + offset;
		while (symbol_pos < 0) {
			symbol_pos += strip.size();
		}
		
		return strip[symbol_pos % strip.size()];
	}
}