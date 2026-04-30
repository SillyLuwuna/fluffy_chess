#include "board.hpp"
#include "board_initializer.hpp"
#include "board_printer.hpp"
#include <iostream>

using namespace fluffy_chess;

int main()
{
	std::string fen_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	Board board;
	// BoardInitializer::initialize_default(board);
	BoardInitializer::initialize_fen(board, fen_str);
	// BoardPrinter::print(board);
	std::string gen_fen = BoardPrinter::get_fen_string(board);

	std::cout << fen_str << '\n';
	std::cout << gen_fen << '\n';
	std::cout << (fen_str == gen_fen) << '\n';

	return 0;
}
