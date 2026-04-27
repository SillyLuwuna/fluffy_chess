#pragma once

#include "board.hpp"
namespace fluffy_chess
{
	class BoardPrinter
	{
		private:
		public:
			static void print(const Board& board);
			constexpr static std::string get_string(const Board& board);
	};
}

using namespace fluffy_chess;

constexpr std::string BoardPrinter::get_string(const Board& board)
{
	std::string board_str;
	board_str.reserve((8 * 4 + 1) * (8 * 4 + 1));

	board_str += "---------------------------------\n";
	for (int i = 7; i >= 0; i--)
	{
		board_str += "|";

		for (int j = 0; j < 8; j++)
		{
			board_str += " ";
			char c = piece_char(board.get_piece_at(gen_bitboard(i, j)));
			board_str += board.get_color_at(gen_bitboard(i, j)) == White ? std::toupper(c) : c;
			board_str += " |";
		}

		board_str += "\n---------------------------------\n";
	}

	board_str += "player: ";
	board_str += board.get
	board_str += "ep_passant: ";
	board_str += bitboard_to_algebraic(board.get_en_passant_square());
	board_str += "\n";

	return board_str;
}
