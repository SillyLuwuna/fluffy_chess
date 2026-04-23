#pragma once

#include "board.hpp"
#include <string>

class BoardInitializer
{
	private:
	public:
		constexpr static void initialize_default(Board& board);
		constexpr static void initialize_fen(Board& board, const std::string& fen);
		constexpr static size_t initialize_fen_placement(Board& board, const std::string& fen, size_t start_idx);
		constexpr static size_t initialize_fen_castling(Board& board, const std::string& fen, size_t start_idx);
		constexpr static size_t initialize_fen_enpassant(Board& board, const std::string& fen, size_t start_idx);
		constexpr static Bitboard algebraic_to_bitboard(File file, Rank rank);
};

#include "board_initializer.ipp"
