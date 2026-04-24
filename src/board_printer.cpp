#include "board_printer.hpp"
#include <iostream>
using namespace fluffy_chess;

void BoardPrinter::print(const Board& board)
{
	std::cout << get_string(board);
}
