#include "Board/Board.h"


static void GetWhiteKingMoves(bool canCastleQS, bool canCastleKS, const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x - 1, y + 1) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 1), Piece::WKing)));
	if (Board::InBoard(x + 0, y + 1) && Board::IsBlack(pieces[Board::ToIndex(x + 0, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 0, y + 1), Piece::WKing)));
	if (Board::InBoard(x + 1, y + 1) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 1), Piece::WKing)));
	if (Board::InBoard(x + 1, y + 0) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y + 0)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 0), Piece::WKing)));
	if (Board::InBoard(x + 1, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y - 1), Piece::WKing)));
	if (Board::InBoard(x + 0, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x + 0, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 0, y - 1), Piece::WKing)));
	if (Board::InBoard(x - 1, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y - 1), Piece::WKing)));
	if (Board::InBoard(x - 1, y + 0) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y + 0)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 0), Piece::WKing)));

	if (canCastleQS && pieces[57] == Piece::None && pieces[58] == Piece::None && pieces[59] == Piece::None) {
		buffer.push_back(Move(Square(60, Piece::None), Square(58, Piece::WKing), Castling::WQ));
	}

	if (canCastleKS && pieces[61] == Piece::None && pieces[62] == Piece::None) {
		buffer.push_back(Move(Square(60, Piece::None), Square(62, Piece::WKing), Castling::WK));
	}
}

static void GetBlackKingMoves(bool canCastleQS, bool canCastleKS, const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x - 1, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 1), Piece::BKing)));
	if (Board::InBoard(x + 0, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x + 0, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 0, y + 1), Piece::BKing)));
	if (Board::InBoard(x + 1, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 1), Piece::BKing)));
	if (Board::InBoard(x + 1, y + 0) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y + 0)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 0), Piece::BKing)));
	if (Board::InBoard(x + 1, y - 1) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y - 1), Piece::BKing)));
	if (Board::InBoard(x + 0, y - 1) && Board::IsWhite(pieces[Board::ToIndex(x + 0, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 0, y - 1), Piece::BKing)));
	if (Board::InBoard(x - 1, y - 1) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y - 1), Piece::BKing)));
	if (Board::InBoard(x - 1, y + 0) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y + 0)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 0), Piece::BKing)));

	if (canCastleQS && pieces[1] == Piece::None && pieces[2] == Piece::None && pieces[3] == Piece::None) {
		buffer.push_back(Move(Square(4, Piece::None), Square(2, Piece::BKing), Castling::BQ));
	}
	if (canCastleKS && pieces[5] == Piece::None && pieces[6] == Piece::None) {
		buffer.push_back(Move(Square(4, Piece::None), Square(6, Piece::BKing), Castling::BK));
	}
}

void Board::getKingMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(8);

	if (isWhite) {
		GetWhiteKingMoves(m_CastleRights[0], m_CastleRights[1], pieces, x, y, buffer);
	}
	else {
		GetBlackKingMoves(m_CastleRights[2], m_CastleRights[3], pieces, x, y, buffer);
	}
}
