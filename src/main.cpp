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

	return 0;
}
