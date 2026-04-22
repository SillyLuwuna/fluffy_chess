#pragma once

#include "types.hpp"
#include <string>

#define NUM_BITBOARDS 6

enum BoardFlags: uint64_t
{
	BLACK_TO_MOVE = 1ULL << 0,
	WHITE_CAN_CASTLE_Q = 1ULL << 1,
	WHITE_CAN_CASTLE_K = 1ULL << 2,
	BLACK_CAN_CASTLE_Q = 1ULL << 3,
	BLACK_CAN_CASTLE_K = 1ULL << 4,
};

class Board
{
	private:
		Bitboard m_bb_all;
		Bitboard m_bb_black;
		Bitboard m_bb_white;

		Bitboard m_bitboards[NUM_BITBOARDS];

		Bitboard m_en_passant;
		uint64_t m_flags;

		uint16_t m_hf_clock;
		uint16_t m_fm_clock;

		constexpr void revoke_castle_wq();
		constexpr void revoke_castle_wk();
		constexpr void revoke_castle_bq();
		constexpr void revoke_castle_bk();

		constexpr void grant_castle_wq();
		constexpr void grant_castle_wk();
		constexpr void grant_castle_bq();
		constexpr void grant_castle_bk();

	public:
		Board(const Board&) = delete;
		Board(Board&&) = delete;
		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = delete;

		Board();
		Board(const std::string& fen);

		void reset();

		void insert_piece(Piece piece, Color color, Rank rank, File file);
		void insert_piece(Piece piece, Color color, uint8_t rank_idx, uint8_t file_idx);
		void insert_piece(Piece piece, Color color, uint8_t idx);
		constexpr void insert_piece(Piece piece, Color color, Bitboard pos_mask);

		constexpr void set_active_color(Color color);

		constexpr void grant_castling(Color color, Piece side);
		constexpr void revoke_castling(Color color, Piece side);
};
