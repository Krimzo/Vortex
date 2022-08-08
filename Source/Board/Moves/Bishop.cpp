#include "Board/Board.h"


static void GetWhiteBishopMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y + i);
		if (Board::InBoard(x + i, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y + i);
		if (Board::InBoard(x - i, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y - i);
		if (Board::InBoard(x + i, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y - i);
		if (Board::InBoard(x - i, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
			}
			else if (Board::IsBlack(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::WBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
}

static void GetBlackBishopMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y + i);
		if (Board::InBoard(x + i, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y + i);
		if (Board::InBoard(x - i, y + i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x + i, y - i);
		if (Board::InBoard(x + i, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = Board::ToIndex(x - i, y - i);
		if (Board::InBoard(x - i, y - i)) {
			if (pieces[index] == Piece::None) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
			}
			else if (Board::IsWhite(pieces[index])) {
				buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(index, Piece::BBishop)));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Board::getBishopMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(13);

	if (isWhite) {
		GetWhiteBishopMoves(pieces, x, y, buffer);
	}
	else {
		GetBlackBishopMoves(pieces, x, y, buffer);
	}
}
