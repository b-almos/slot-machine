#include "ReelSet.h"
#include "Paylines.h"
#include "Constants.h"
#include "Types.h"

int main()
{
	slot::ReelSet game_grid;

	std::array<int, 5> stop_pos{ 1, 1, 1, 1, 1 };
	game_grid.spin(stop_pos);
	game_grid.print();
	slot::Paylines paylines;

	std::array<slot::PaylineResult, slot::payline_count> payline_results = paylines.evaluatePaylines(game_grid.getGrid());
}