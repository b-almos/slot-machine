#pragma once

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
}