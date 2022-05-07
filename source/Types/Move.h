#pragma once

#include "Types/Square.h"


class Move {
public:
	enum class Castling {
		None = 0,
		WK,
		WQ,
		BK,
		BQ
	};

	Square from;
	Square to;
	Castling castling;

	Move() : castling(Castling::None) {}
	Move(Square from, Square to, Castling castling = Castling::None) : from(from), to(to), castling(castling) {}
};
