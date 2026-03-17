#pragma once

#include "Symbol.h"
#include <vector>

namespace slot {
	class Reel {
	private:
		std::vector<Symbol> strip;
	public:
		Reel(std::vector<Symbol>);
		std::vector<Symbol> getShowingSymbols(const int stop_position);
		Symbol getSymbolAt(const int stop_position, const int offset);
	};
}