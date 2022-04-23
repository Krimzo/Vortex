#pragma once

#include "Piece.h"


class Square {
public:
	int index;
	Piece::Type piece;

	Square();
	Square(int index, Piece::Type piece);
};
