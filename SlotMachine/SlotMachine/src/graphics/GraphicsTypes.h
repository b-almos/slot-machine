#pragma once

#include <string>
#include "core/Types.h"

namespace slot::gfx {
	enum class PendingAction { None, Push, Pop, Replace };

	inline std::string symbolToTextureKey(Symbol symbol)
	{
		switch (symbol) {
		case Symbol::Cherry:
			return "cherry";
		case Symbol::Lemon:
			return "lemon";
		case Symbol::Orange:
			return "orange";
		case Symbol::Plum:
			return "plum";
		case Symbol::Watermelon:
			return "watermelon";
		case Symbol::Grapes:
			return "grape";
		case Symbol::Bell:
			return "bell";
		case Symbol::Seven:
			return "seven";
		default:
			return "unknown";
		}
	}
}