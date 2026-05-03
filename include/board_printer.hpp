#pragma once

#include "board.hpp"
namespace fluffy_chess
{
	class BoardPrinter
	{
		private:
			constexpr static std::string get_fen_castling_rights(const Board& board);
			constexpr static std::string get_fen_board(const Board& board);
			constexpr static std::string get_fen_rank(const Board& board, int rank);
			constexpr static char get_fen_piece_at(const Board& board, Bitboard pos);
			constexpr static std::string get_fen_player(const Board& board);
			constexpr static std::string get_fen_en_passant(const Board& board);
			constexpr static std::string get_fen_hc(const Board& board);
			constexpr static std::string get_fen_fc(const Board& board);

		public:
			static void print(const Board& board);
			constexpr static std::string get_string(const Board& board);
			constexpr static std::string get_fen_string(const Board& board);
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
			board_str += " " + std::to_string(get_fen_piece_at(board, gen_bitboard(i, j))) + " |";
		}

		board_str += "\n---------------------------------\n";
	}

	board_str += "player: " + get_fen_player(board) + "\n";
	board_str += "castling_rights: " + get_fen_castling_rights(board) + "\n";
	board_str += "ep_passant: " + get_fen_en_passant(board) + "\n";
	board_str += "half_clock: " + get_fen_hc(board) + "\n";
	board_str += "full_clock: " + get_fen_fc(board) + "\n";

	return board_str;
}

constexpr std::string BoardPrinter::get_fen_string(const Board& board)
{
	std::string fen_str;

	fen_str += get_fen_board(board) + " ";
	fen_str += get_fen_player(board) + " ";
	fen_str += get_fen_castling_rights(board) + " ";
	fen_str += get_fen_en_passant(board) + " ";
	fen_str += get_fen_hc(board) + " ";
	fen_str += get_fen_fc(board);

	return fen_str;
}

constexpr std::string BoardPrinter::get_fen_board(const Board& board)
{
	std::string fen_str;
	
	for (int i = 7; i >= 0; i--)
	{
		fen_str += get_fen_rank(board, i);

		if (i > 0)
		{
			fen_str += "/";
		}
	}

	return fen_str;
}

constexpr std::string BoardPrinter::get_fen_rank(const Board& board, int rank)
{
	std::string fen_str;

	uint8_t no_piece_counter = 0;
	for (int i = 0; i < 8; i++)
	{
		Bitboard pos = gen_bitboard(rank, i);

		if (!board.has_piece_at(pos))
		{
			no_piece_counter++;
			continue;
		}

		fen_str += no_piece_counter > 0 ? std::to_string(no_piece_counter) : "";
		fen_str += get_fen_piece_at(board, pos);

		no_piece_counter = 0;
	}

	fen_str += no_piece_counter > 0 ? std::to_string(no_piece_counter) : "";

	return fen_str;
}

constexpr char BoardPrinter::get_fen_piece_at(const Board& board, Bitboard pos)
{
	char c = piece_char(board.get_piece_at(pos));
	return board.get_color_at(pos) == White ? std::toupper(c) : c;
}

constexpr std::string BoardPrinter::get_fen_castling_rights(const Board& board)
{
	std::string fen_str;

	fen_str += board.white_can_castle_king_side() ? "K" : "";
	fen_str += board.white_can_castle_queen_side() ? "Q" : "";
	fen_str += board.black_can_castle_king_side() ? "k" : "";
	fen_str += board.black_can_castle_queen_side() ? "q" : "";

	if (fen_str == "")
	{
		fen_str = "-";
	}

	return fen_str;
}

constexpr std::string BoardPrinter::get_fen_player(const Board& board)
{
	return board.is_black_playing() ? "b" : "w";
}

constexpr std::string BoardPrinter::get_fen_en_passant(const Board& board)
{
	Bitboard en_passant_square = board.get_en_passant_square();
	return en_passant_square != 0ULL ? bitboard_to_algebraic(en_passant_square) : "-";
}

constexpr std::string BoardPrinter::get_fen_hc(const Board& board)
{
	return std::to_string(board.get_hm_clock());
}

constexpr std::string BoardPrinter::get_fen_fc(const Board& board)
{
	return std::to_string(board.get_fm_clock());
}

