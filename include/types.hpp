#pragma once
#include <cstdint>

namespace fluffy_chess
{
	using Bitboard = uint64_t;

	enum Piece: uint8_t
	{
		Pawn,
		Knight,
		Bishop,
		Rook,
		Queen,
		King,
		PieceNum,
	};

	enum Color: bool
	{
		White = true,
		Black = false
	};

	enum File: uint8_t
	{
		F_A = 'A',
		F_B = 'B',
		F_C = 'C',
		F_D = 'D',
		F_E = 'E',
		F_F = 'F',
		F_G = 'G',
		F_H = 'H'
	};

	enum Rank: uint8_t
	{
		R_1 = 1,
		R_2 = 2,
		R_3 = 3,
		R_4 = 4,
		R_5 = 5,
		R_6 = 6,
		R_7 = 7,
		R_8 = 8,
	};

	constexpr Piece parse_piece(char c)
	{
		Piece piece = PieceNum;

		switch (c)
		{
			case 'p':
				piece = Pawn;
				break;
			case 'r':
				piece = Rook;
				break;
			case 'n':
				piece = Knight;
				break;
			case 'b':
				piece = Bishop;
				break;
			case 'q':
				piece = Queen;
				break;
			case 'k':
				piece = King;
				break;
		}

		return piece;
	}

	constexpr char piece_char(Piece piece)
	{
		char c = ' ';

		switch (piece)
		{
			case Pawn:
				c = 'p';
				break;
			case Rook:
				c = 'r';
				break;
			case Knight:
				c = 'n';
				break;
			case Bishop:
				c = 'b';
				break;
			case Queen:
				c = 'q';
				break;
			case King:
				c = 'k';
				break;
			case PieceNum:
				c = ' ';
				break;
		}

		return c;
	}

	constexpr inline static Bitboard gen_bitboard(uint8_t idx)
	{
		return 1ULL << idx;
	}

	constexpr inline static Bitboard gen_bitboard(uint8_t rank_idx, uint8_t file_idx)
	{
		return gen_bitboard((uint8_t)(8 * rank_idx + file_idx));
	}

	constexpr inline static Bitboard gen_bitboard(Rank rank, File file)
	{
		return gen_bitboard(rank - R_1, file - F_A);
	}
}
