#pragma once

#include <cstdint>

using Bitboard = uint64_t;

// enum Piece: uint8_t
// {
// 	Pawn = 'p',
// 	Knight = 'n',
// 	Bishop = 'b',
// 	Rook = 'r',
// 	Queen = 'q',
// 	King = 'k'
// };

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
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',
	G = 'G',
	H = 'H',
};

enum Rank: uint8_t
{
	R1 = 1,
	R2 = 2,
	R3 = 3,
	R4 = 4,
	R5 = 5,
	R6 = 6,
	R7 = 7,
	R8 = 8,
};
