#include "Board/Board.h"


void Board::wRookMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(14);

	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y);
		if (inBoard(x + i, y)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y);
		if (inBoard(x - i, y)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x, y + i);
		if (inBoard(x, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x, y - i);
		if (inBoard(x, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Board::bRookMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(14);

	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y);
		if (inBoard(x + i, y)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y);
		if (inBoard(x - i, y)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x, y + i);
		if (inBoard(x, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x, y - i);
		if (inBoard(x, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}
}
