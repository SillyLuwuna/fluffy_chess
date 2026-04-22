#include "board.hpp"
#include "board_initializer.hpp"
#include <cstring>

Board::Board()
{
	reset();
}

Board::Board(const std::string& fen) : Board()
{
	BoardInitializer::initialize_fen(*this, fen);
}

void Board::reset()
{
	m_bb_all = 0;
	m_bb_black = 0;
	m_bb_white = 0;
	std::memset(m_bitboards, 0, NUM_BITBOARDS * sizeof(Bitboard));
	m_en_passant = 0;
	m_flags = 0;
	m_hf_clock = 0;
	m_fm_clock = 0;
}

void Board::insert_piece(Piece piece, Color color, Rank rank, File file)
{
	insert_piece(piece, color, rank - 1, file - 'A');
}

void Board::insert_piece(Piece piece, Color color, uint8_t rank_idx, uint8_t file_idx)
{
	insert_piece(piece, color, (uint8_t)(8 * rank_idx + file_idx));
}

void Board::insert_piece(Piece piece, Color color, uint8_t idx)
{
	insert_piece(piece, color, (uint64_t)(1ULL << idx));
}

constexpr void Board::insert_piece(Piece piece, Color color, uint64_t pos_mask)
{
	m_bb_all |= pos_mask;
	(color == White ? m_bb_white : m_bb_black) |= pos_mask;
	m_bitboards[piece] |= pos_mask;
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
