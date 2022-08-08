#include "Board/Board.h"


static void GetWhitePawnMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x, y - 1) && pieces[Board::ToIndex(x, y - 1)] == Piece::None) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));

		if (y == 6 && pieces[Board::ToIndex(x, y - 2)] == Piece::None) {
			buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x, y - 2), Piece::WPawn)));
		}
	}

	if (Board::InBoard(x - 1, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y - 1)])) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));
	}
	if (Board::InBoard(x + 1, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y - 1)])) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y - 1), (y == 1) ? Piece::WQueen : Piece::WPawn)));
	}
}

static void GetBlackPawnMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x, y + 1) && pieces[Board::ToIndex(x, y + 1)] == Piece::None) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));

		if (y == 1 && pieces[Board::ToIndex(x, y + 2)] == Piece::None) {
			buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x, y + 2), Piece::BPawn)));
		}
	}

	if (Board::InBoard(x - 1, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y + 1)])) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));
	}
	if (Board::InBoard(x + 1, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y + 1)])) {
		buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 1), (y == 6) ? Piece::BQueen : Piece::BPawn)));
	}
}

void Board::getPawnMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(4);

	if (isWhite) {
		GetWhitePawnMoves(pieces, x, y, buffer);
	}
	else {
		GetBlackPawnMoves(pieces, x, y, buffer);
	}
}
