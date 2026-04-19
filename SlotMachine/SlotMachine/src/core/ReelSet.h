#pragma once

#include "Reel.h"
#include "Constants.h"
#include <array>
#include <iostream>

namespace slot {
	class ReelSet {
	private:
		
		//////////////////////////////////////////////////////////////////////////////////////////////////
		// hardcoded strips for the 5 reels

		static constexpr std::array<Symbol, strip_size> strip_1 = { 
			Symbol::Cherry, Symbol::Lemon, Symbol::Orange, Symbol::Plum,
			Symbol::Watermelon, Symbol::Grapes, Symbol::Bell, Symbol::Cherry,
			Symbol::Lemon, Symbol::Orange, Symbol::Plum, Symbol::Watermelon,
			Symbol::Grapes, Symbol::Bell, Symbol::Cherry, Symbol::Lemon,
			Symbol::Orange, Symbol::Plum, Symbol::Watermelon, Symbol::Grapes,
			Symbol::Bell, Symbol::Cherry, Symbol::Lemon, Symbol::Orange,
			Symbol::Cherry, Symbol::Lemon, Symbol::Orange, Symbol::Grapes,
			Symbol::Watermelon, Symbol::Plum, Symbol::Cherry, Symbol::Seven 
		};
		static constexpr std::array<Symbol, strip_size> strip_2 = {
			Symbol::Lemon, Symbol::Cherry, Symbol::Orange, Symbol::Grapes,
			Symbol::Watermelon, Symbol::Plum, Symbol::Bell, Symbol::Lemon,
			Symbol::Cherry, Symbol::Orange, Symbol::Grapes, Symbol::Watermelon,
			Symbol::Plum, Symbol::Bell, Symbol::Lemon, Symbol::Cherry,
			Symbol::Orange, Symbol::Grapes, Symbol::Watermelon, Symbol::Plum,
			Symbol::Bell, Symbol::Lemon, Symbol::Cherry, Symbol::Orange,
			Symbol::Lemon, Symbol::Cherry, Symbol::Grapes, Symbol::Watermelon,
			Symbol::Plum, Symbol::Orange, Symbol::Lemon, Symbol::Seven 
		};
		static constexpr std::array<Symbol, strip_size> strip_3 = {
			Symbol::Orange, Symbol::Cherry, Symbol::Lemon, Symbol::Plum,
			Symbol::Grapes, Symbol::Watermelon, Symbol::Bell, Symbol::Orange,
			Symbol::Cherry, Symbol::Lemon, Symbol::Plum, Symbol::Grapes,
			Symbol::Watermelon, Symbol::Bell, Symbol::Orange, Symbol::Cherry,
			Symbol::Lemon, Symbol::Plum, Symbol::Grapes, Symbol::Watermelon,
			Symbol::Bell, Symbol::Orange, Symbol::Cherry, Symbol::Lemon,
			Symbol::Orange, Symbol::Cherry, Symbol::Lemon, Symbol::Grapes,
			Symbol::Watermelon, Symbol::Plum, Symbol::Orange, Symbol::Seven
		};
		static constexpr std::array<Symbol, strip_size> strip_4 = {
			Symbol::Cherry, Symbol::Orange, Symbol::Lemon, Symbol::Grapes,
			Symbol::Plum, Symbol::Watermelon, Symbol::Bell, Symbol::Cherry,
			Symbol::Orange, Symbol::Lemon, Symbol::Grapes, Symbol::Plum,
			Symbol::Watermelon, Symbol::Bell, Symbol::Cherry, Symbol::Orange,
			Symbol::Lemon, Symbol::Grapes, Symbol::Plum, Symbol::Watermelon,
			Symbol::Bell, Symbol::Cherry, Symbol::Orange, Symbol::Lemon,
			Symbol::Cherry, Symbol::Orange, Symbol::Grapes, Symbol::Watermelon,
			Symbol::Plum, Symbol::Lemon, Symbol::Cherry, Symbol::Seven
		};
		static constexpr std::array<Symbol, strip_size> strip_5 = {
			Symbol::Lemon, Symbol::Orange, Symbol::Cherry, Symbol::Plum,
			Symbol::Watermelon, Symbol::Grapes, Symbol::Bell, Symbol::Lemon,
			Symbol::Orange, Symbol::Cherry, Symbol::Plum, Symbol::Watermelon,
			Symbol::Grapes, Symbol::Bell, Symbol::Lemon, Symbol::Orange,
			Symbol::Cherry, Symbol::Plum, Symbol::Watermelon, Symbol::Grapes,
			Symbol::Bell, Symbol::Lemon, Symbol::Orange, Symbol::Cherry,
			Symbol::Lemon, Symbol::Orange, Symbol::Cherry, Symbol::Grapes,
			Symbol::Watermelon, Symbol::Plum, Symbol::Lemon, Symbol::Seven
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////

		std::array<Reel, reels_count> reels;
		std::array<std::array<Symbol, reels_count>, rows_count> grid;
	public:
		ReelSet();
		void spin(const std::array<int, reels_count>&);
		void print() const;
		const std::array<std::array<Symbol, reels_count>, rows_count>& getGrid() const;
		const Symbol getSymbolAt(const int reel, const int stop_position, const int offset) const;
	};
}