#include "board.hpp"
#include "board_initializer.hpp"
#include "board_printer.hpp"
#include <iostream>

using namespace fluffy_chess;

int main()
{
	Board board;
	BoardInitializer::initialize_default(board);
	BoardPrinter::print(board);

	// TODO: make fen string from board. Truly a good test.

	// std::cout << piece_char(board.get_piece_at(gen_bitboard(0))) << '\n';
	return 0;
}
