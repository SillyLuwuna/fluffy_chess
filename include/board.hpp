#pragma once

#include "types.hpp"
#include <string>

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
		static constexpr uint64_t NUM_BITBOARDS = 6;

		Bitboard m_bb_all;
		Bitboard m_bb_black;
		Bitboard m_bb_white;

		Bitboard m_bitboards[NUM_BITBOARDS];

		Bitboard m_en_passant;
		uint64_t m_flags;

		uint16_t m_hf_clock;
		uint16_t m_fm_clock;

		inline constexpr void revoke_castle_wq();
		inline constexpr void revoke_castle_wk();
		inline constexpr void revoke_castle_bq();
		inline constexpr void revoke_castle_bk();

		inline constexpr void grant_castle_wq();
		inline constexpr void grant_castle_wk();
		inline constexpr void grant_castle_bq();
		inline constexpr void grant_castle_bk();

	public:
		Board(const Board&) = delete;
		Board(Board&&) = delete;
		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = delete;

		constexpr Board();
		constexpr Board(const std::string& fen);

		constexpr void reset();

		constexpr void insert_piece(Piece piece, Color color, Rank rank, File file);
		constexpr void insert_piece(Piece piece, Color color, uint8_t rank_idx, uint8_t file_idx);
		constexpr void insert_piece(Piece piece, Color color, uint8_t idx);

		constexpr void insert_piece(Piece piece, Color color, Bitboard pos_mask);
		constexpr void set_active_color(Color color);
		constexpr void grant_castling(Color color, Piece side);
		constexpr void revoke_castling(Color color, Piece side);
		constexpr void set_en_passant_square(Bitboard square);
};

#include "board.ipp"
