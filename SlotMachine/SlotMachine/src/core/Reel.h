#pragma once

#include "Types.h"
#include "Constants.h"
#include <array>

namespace slot {
	class Reel {
	private:
		std::array<Symbol, strip_size> strip;
	public:
		Reel();
		Reel(std::array<Symbol, strip_size>);
		const std::array<Symbol, rows_count> getShowingSymbols(const int stop_position) const;
		const Symbol getSymbolAt(const int stop_position, const int offset) const;
	};
}