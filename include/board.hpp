#pragma once
#include "types.hpp"
#include <cstring>
#include <iostream>
#include <string>

namespace fluffy_chess
{
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
			static constexpr uint64_t NUM_BITBOARDS = PieceNum;

			Bitboard m_bb_all;
			Bitboard m_bb_black;
			Bitboard m_bb_white;
			Bitboard m_bb_piece[NUM_BITBOARDS];

			Bitboard m_en_passant;
			uint64_t m_flags;

			uint16_t m_hm_clock;
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

			constexpr void reset();

			constexpr void insert_piece(Piece piece, Color color, Bitboard pos_mask);
			constexpr void set_active_color(Color color);
			constexpr void grant_castling(Color color, Piece side);
			constexpr void revoke_castling(Color color, Piece side);
			constexpr void set_en_passant_square(Bitboard square);
			constexpr void set_hm_clock(uint16_t value);
			constexpr void set_fm_clock(uint16_t value);

			constexpr Piece get_piece_at(Bitboard pos_mask) const;
			constexpr Color get_color_at(Bitboard pos_mask) const;
			constexpr Bitboard get_en_passant_square() const;
			constexpr uint64_t get_flags() const;
			constexpr uint16_t get_hm_clock() const;
			constexpr uint16_t get_fm_clock() const;
			constexpr bool is_black_playing() const;
			constexpr bool black_can_castle_king_side() const;
			constexpr bool black_can_castle_queen_side() const;
			constexpr bool white_can_castle_king_side() const;
			constexpr bool white_can_castle_queen_side() const;
	};
}

using namespace fluffy_chess;

constexpr Board::Board()
{
	reset();
}

constexpr void Board::reset()
{
	m_bb_all = 0;
	m_bb_black = 0;
	m_bb_white = 0;
	if (std::is_constant_evaluated())
	{
		for (uint64_t i = 0; i < 6; i++)
		{
			m_bb_piece[i] = 0;
		}
	}
	else
	{
		std::memset(m_bb_piece, 0, NUM_BITBOARDS * sizeof(Bitboard));
	}
	m_en_passant = 0;
	m_flags = 0;
	m_hm_clock = 0;
	m_fm_clock = 0;
}

constexpr void Board::insert_piece(Piece piece, Color color, uint64_t pos_mask)
{
	m_bb_all |= pos_mask;
	(color == White ? m_bb_white : m_bb_black) |= pos_mask;
	m_bb_piece[piece] |= pos_mask;
}

constexpr void Board::set_active_color(Color color)
{
	m_flags &= ~BLACK_TO_MOVE;
	if (color == Black)
	{
		m_flags |= BLACK_TO_MOVE;
	}
}

constexpr void Board::revoke_castle_wq() { m_flags &= ~WHITE_CAN_CASTLE_Q; }
constexpr void Board::revoke_castle_wk() { m_flags &= ~WHITE_CAN_CASTLE_K; }
constexpr void Board::revoke_castle_bq() { m_flags &= ~BLACK_CAN_CASTLE_Q; }
constexpr void Board::revoke_castle_bk() { m_flags &= ~BLACK_CAN_CASTLE_K; }

constexpr void Board::grant_castle_wq() { m_flags |= WHITE_CAN_CASTLE_Q; }
constexpr void Board::grant_castle_wk() { m_flags |= WHITE_CAN_CASTLE_K; }
constexpr void Board::grant_castle_bq() { m_flags |= BLACK_CAN_CASTLE_Q; }
constexpr void Board::grant_castle_bk() { m_flags |= BLACK_CAN_CASTLE_K; }

constexpr void Board::grant_castling(Color color, Piece side)
{
	if (color == White && side == King)
	{
		grant_castle_wk();
	}
	else if (color == White && side == Queen)
	{
		grant_castle_wq();
	}
	else if (color == Black && side == King)
	{
		grant_castle_bk();
	}
	else if (color == Black && side == Queen)
	{
		grant_castle_bq();
	}
}

constexpr void Board::revoke_castling(Color color, Piece side)
{
	if (color == White && side == King)
	{
		revoke_castle_wk();
	}
	else if (color == White && side == Queen)
	{
		revoke_castle_wq();
	}
	else if (color == Black && side == King)
	{
		revoke_castle_bk();
	}
	else if (color == Black && side == Queen)
	{
		revoke_castle_bq();
	}
}

constexpr void Board::set_en_passant_square(Bitboard square)
{
	m_en_passant = square;
}

constexpr void Board::set_hm_clock(uint16_t value)
{
	m_hm_clock = value;
}

constexpr void Board::set_fm_clock(uint16_t value)
{
	m_fm_clock = value;
}

constexpr Piece Board::get_piece_at(Bitboard pos_mask) const
{
	for (size_t i = 0; i < NUM_BITBOARDS; i++)
	{
		if (pos_mask & m_bb_piece[i])
		{
			return (Piece)i;
		}
	}
	return PieceNum;
}

constexpr Color Board::get_color_at(Bitboard pos_mask) const
{
	return pos_mask & m_bb_black ? Black : White;
}

constexpr Bitboard Board::get_en_passant_square() const
{
	return m_en_passant;
}

constexpr uint64_t Board::get_flags() const
{
	return m_flags;
}

constexpr uint16_t Board::get_hm_clock() const
{
	return m_hm_clock;
}

constexpr uint16_t Board::get_fm_clock() const
{
	return m_fm_clock;
}

constexpr bool Board::is_black_playing() const
{
	return m_flags & BLACK_TO_MOVE;
}

constexpr bool Board::black_can_castle_king_side() const
{
	return m_flags & BLACK_CAN_CASTLE_K;
}

constexpr bool Board::black_can_castle_queen_side() const
{
	return m_flags & BLACK_CAN_CASTLE_Q;
}

constexpr bool Board::white_can_castle_king_side() const
{
	return m_flags & WHITE_CAN_CASTLE_K;
}

constexpr bool Board::white_can_castle_queen_side() const
{
	return m_flags & WHITE_CAN_CASTLE_Q;
}
