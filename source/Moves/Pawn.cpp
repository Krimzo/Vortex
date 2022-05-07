#include "Board/Board.h"


void Board::wPawnMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(4);

	// Moving
	if (inBoard(x, y - 1) && pieces[toi(x, y - 1)] == Piece::None) {
		// Moving 1 y up
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));

		// Moving 2 y up
		if (y == 6 && pieces[toi(x, y - 2)] == Piece::None) {
			outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x, y - 2), Piece::WPawn)));
		}
	}

	// Eating
	// Left
	if (inBoard(x - 1, y - 1) && isBlack(pieces[toi(x - 1, y - 1)])) {
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));
	}
	// Right
	if (inBoard(x + 1, y - 1) && isBlack(pieces[toi(x + 1, y - 1)])) {
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));
	}
}

void Board::bPawnMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(4);

	// Moving
	if (inBoard(x, y + 1) && pieces[toi(x, y + 1)] == Piece::None) {
		// Moving 1 y up
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));

		// Moving 2 y up
		if (y == 1 && pieces[toi(x, y + 2)] == Piece::None) {
			outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x, y + 2), Piece::BPawn)));
		}
	}

	// Eating
	// Left
	if (inBoard(x - 1, y + 1) && isWhite(pieces[toi(x - 1, y + 1)])) {
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));
	}
	// Right
	if (inBoard(x + 1, y + 1) && isWhite(pieces[toi(x + 1, y + 1)])) {
		outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));
	}
}
