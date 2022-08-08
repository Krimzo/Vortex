#include "Board/Board.h"


static void GetWhiteRookMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y);
		if (Board::InBoard(x + i, y)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y);
		if (Board::InBoard(x - i, y)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x, y + i);
		if (Board::InBoard(x, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x, y - i);
		if (Board::InBoard(x, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WRook)));
				break;
			}
			else {
				break;
			}
		}
	}
}

static void GetBlackRookMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y);
		if (Board::InBoard(x + i, y)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y);
		if (Board::InBoard(x - i, y)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x, y + i);
		if (Board::InBoard(x, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x, y - i);
		if (Board::InBoard(x, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BRook)));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Board::getRookMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(14);

	if (isWhite) {
		GetWhiteRookMoves(pieces, x, y, buffer);
	}
	else {
		GetBlackRookMoves(pieces, x, y, buffer);
	}
}
