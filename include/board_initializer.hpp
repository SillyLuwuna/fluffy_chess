#pragma once
#include "board.hpp"
#include "types.hpp"
#include <iostream>
#include <string>

namespace fluffy_chess
{
	class BoardInitializer
	{
		private:
			constexpr static size_t initialize_fen_placement(Board& board, const std::string& fen, size_t start_idx);
			constexpr static size_t initialize_fen_castling(Board& board, const std::string& fen, size_t start_idx);
			constexpr static size_t initialize_fen_enpassant(Board& board, const std::string& fen, size_t start_idx);

		public:
			constexpr static void initialize_default(Board& board);
			constexpr static void initialize_fen(Board& board, const std::string& fen);
	};
}

using namespace fluffy_chess;

constexpr void BoardInitializer::initialize_default(Board& board)
{
	initialize_fen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

constexpr void BoardInitializer::initialize_fen(Board& board, const std::string& fen)
{
	board.reset();
	size_t str_idx = initialize_fen_placement(board, fen, 0);
	board.set_active_color((Color)(bool)(fen[str_idx] == 'w'));
	str_idx = initialize_fen_castling(board, fen, str_idx + 2);
	str_idx = initialize_fen_enpassant(board, fen, str_idx);
	size_t last_space_idx = fen.find_last_of(' ');
	board.set_hm_clock(std::stoi(fen.substr(str_idx, str_idx - last_space_idx)));
	board.set_fm_clock(std::stoi(fen.substr(last_space_idx + 1)));
}

constexpr size_t BoardInitializer::initialize_fen_placement(Board& board, const std::string& fen, size_t start_idx)
{
	Bitboard bb_curr = 1ULL << 56;

	char curr_char;
	while ((curr_char = fen[start_idx++]) != ' ')
	{
		if (bb_curr == 0ULL && curr_char == '/')
		{
			bb_curr = 1ULL << 48;
			continue;
		}

		if (curr_char == '/')
		{
			bb_curr >>= 16;
			continue;
		}

		if (std::isdigit(curr_char))
		{
			bb_curr <<= (curr_char - '0');
			continue;
		}

		board.insert_piece(parse_piece(std::tolower(curr_char)), (Color)(bool)std::isupper(curr_char), bb_curr);

		bb_curr <<= 1;
	}

	return start_idx;
}

constexpr size_t BoardInitializer::initialize_fen_castling(Board& board, const std::string& fen, size_t start_idx)
{
	board.revoke_castling(White, King);
	board.revoke_castling(White, Queen);
	board.revoke_castling(Black, King);
	board.revoke_castling(Black, Queen);

	if (fen[start_idx] == '-')
	{
		return start_idx + 2;
	}

	char curr_char;
	while ((curr_char = fen[start_idx++]) != ' ')
	{
		Color color = (Color)(bool)std::isupper(curr_char);
		Piece side = parse_piece(std::tolower(curr_char));
		board.grant_castling(color, side);
	}

	return start_idx;
}

constexpr size_t BoardInitializer::initialize_fen_enpassant(Board& board, const std::string& fen, size_t start_idx)
{
	if (fen[start_idx] == '-')
	{
		return start_idx + 2;
	}

	File file = (File)std::toupper(fen[start_idx]);
	Rank rank = idx_to_rank(fen[start_idx + 1] - '0');
	board.set_en_passant_square(algebraic_to_bitboard(file, rank));

	return start_idx + 3;
}
