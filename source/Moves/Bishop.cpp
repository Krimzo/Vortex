#include "Board/Board.h"


void Board::wBishopMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(13);

	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y + i);
		if (inBoard(x + i, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y + i);
		if (inBoard(x - i, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y - i);
		if (inBoard(x + i, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y - i);
		if (inBoard(x - i, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
			}
			else if (isBlack(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Board::bBishopMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(13);

	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y + i);
		if (inBoard(x + i, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y + i);
		if (inBoard(x - i, y + i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x + i, y - i);
		if (inBoard(x + i, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		const int ind = toi(x - i, y - i);
		if (inBoard(x - i, y - i)) {
			if (pieces[ind] == Piece::None) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
			}
			else if (isWhite(pieces[ind])) {
				outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(ind, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
}
