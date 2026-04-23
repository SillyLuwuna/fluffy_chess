#pragma once

#include "board_initializer.hpp"

constexpr void BoardInitializer::initialize_default(Board& board)
{
	initialize_fen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

constexpr void BoardInitializer::initialize_fen(Board& board, const std::string& fen)
{
	board.reset();
	size_t str_idx = initialize_fen_placement(board, fen, 0);
	board.set_active_color((Color)(fen[str_idx] == 'w'));
	str_idx = initialize_fen_castling(board, fen, str_idx + 2);
	str_idx = initialize_fen_enpassant(board, fen, str_idx);
}

constexpr size_t BoardInitializer::initialize_fen_placement(Board& board, const std::string& fen, size_t start_idx)
{
	Bitboard bb_curr = 1ULL << 56;

	char curr_char;
	while ((curr_char = fen[start_idx++]) != ' ')
	{
		if (curr_char == '/')
		{
			bb_curr >>= 15;
			continue;
		}

		if (std::isdigit(curr_char))
		{
			bb_curr <<= (curr_char - '0');
			continue;
		}

		board.insert_piece(parse_piece(std::tolower(curr_char)), (Color)std::isupper(curr_char), bb_curr);
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
		Color color = (Color)std::isupper(curr_char);
		Piece side = parse_piece(curr_char);
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
	Rank rank = (Rank)(fen[start_idx + 1] - '0');
	board.set_en_passant_square(algebraic_to_bitboard(file, rank));

	return start_idx + 3;
}

constexpr Bitboard BoardInitializer::algebraic_to_bitboard(File file, Rank rank)
{
	return 1ULL << (8 * (rank - R_1) + (file - F_A));
}
