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
	board_str += board.is_black_playing() ? "black\n" : "white\n";

	board_str += "castling_rights: ";
	board_str += board.white_can_castle_king_side() ? "K" : "";
	board_str += board.white_can_castle_queen_side() ? "Q" : "";
	board_str += board.black_can_castle_king_side() ? "k" : "";
	board_str += board.black_can_castle_queen_side() ? "q" : "";
	board_str += "\n";

	board_str += "ep_passant: ";
	Bitboard en_passant_square = board.get_en_passant_square();
	board_str += en_passant_square != 0ULL ? bitboard_to_algebraic(en_passant_square) : "-";
	board_str += "\n";

	board_str += "half_clock: ";
	board_str += std::to_string(board.get_hm_clock());
	board_str += "\n";
	board_str += "full_clock: ";
	board_str += std::to_string(board.get_fm_clock());
	board_str += "\n";

	return board_str;
}
