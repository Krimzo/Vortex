#include "Chess/Piece.h"


Piece::Piece() {
	type = Piece::Type::None;
}
Piece::Piece(Piece::Type type) {
	this->type = type;
}

// Returns piece type
int Piece::color() const {
	switch (this->type) {
		// White piece
	case Piece::Type::WPawn:
	case Piece::Type::WKnight:
	case Piece::Type::WBishop:
	case Piece::Type::WRook:
	case Piece::Type::WQueen:
	case Piece::Type::WKing:
		return 1;

		// Black piece
	case Piece::Type::BPawn:
	case Piece::Type::BKnight:
	case Piece::Type::BBishop:
	case Piece::Type::BRook:
	case Piece::Type::BQueen:
	case Piece::Type::BKing:
		return -1;

		// None
	default:
		return 0;
	}
}
