#pragma once

#include "Chess/Piece.h"


struct Square {
	int index;
	Piece::Type piece;

	Square() {
		index = -1;
		piece = Piece::Type::None;
	}
	Square(int index, Piece::Type piece) {
		this->index = index;
		this->piece = piece;
	}
};

class Move {
public:
	Square from;
	Square to;

	Move() {

	}
	Move(Square from, Square to) {
		this->from = from;
		this->to = to;
	}
};
