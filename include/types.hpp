#pragma once

#include <cstdint>

using Bitboard = uint64_t;

enum Piece: uint8_t
{
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
	NumPieces,
};

inline Piece parse_piece(char c)
{
	Piece piece;

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
	F_H = 'H',
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
