#pragma once

#include "Types/Piece.h"


class Square {
public:
	int index = -1;
	Piece piece = Piece::None;

	Square() {}
	Square(int index, const Piece& piece) : index(index), piece(piece) {}
};
