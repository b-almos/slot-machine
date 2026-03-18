#include "ReelSet.h"

int main()
{
	slot::ReelSet game_grid;

	std::array<int, 5> stop_pos{ 3, 7, 22, 32, 11 };
	game_grid.spin(stop_pos);
	game_grid.print();
}