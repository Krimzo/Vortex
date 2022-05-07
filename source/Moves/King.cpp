#include "Board/Board.h"


void Board::wKingMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(8);

	if (inBoard(x - 1, y + 1) && isBlack(pieces[toi(x - 1, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 1), Piece::WKing)));
	if (inBoard(x + 0, y + 1) && isBlack(pieces[toi(x + 0, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 0, y + 1), Piece::WKing)));
	if (inBoard(x + 1, y + 1) && isBlack(pieces[toi(x + 1, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 1), Piece::WKing)));
	if (inBoard(x + 1, y + 0) && isBlack(pieces[toi(x + 1, y + 0)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 0), Piece::WKing)));
	if (inBoard(x + 1, y - 1) && isBlack(pieces[toi(x + 1, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y - 1), Piece::WKing)));
	if (inBoard(x + 0, y - 1) && isBlack(pieces[toi(x + 0, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 0, y - 1), Piece::WKing)));
	if (inBoard(x - 1, y - 1) && isBlack(pieces[toi(x - 1, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y - 1), Piece::WKing)));
	if (inBoard(x - 1, y + 0) && isBlack(pieces[toi(x - 1, y + 0)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 0), Piece::WKing)));

	if (wCanCastleQ && pieces[57] == Piece::None && pieces[58] == Piece::None && pieces[59] == Piece::None) {
		outMoves.push_back(Move(Square(60, Piece::None), Square(58, Piece::WKing), Move::Castling::WQ));
	}
	if (wCanCastleK && pieces[61] == Piece::None && pieces[62] == Piece::None) {
		outMoves.push_back(Move(Square(60, Piece::None), Square(62, Piece::WKing), Move::Castling::WK));
	}
}

void Board::bKingMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(8);

	if (inBoard(x - 1, y + 1) && isWhite(pieces[toi(x - 1, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 1), Piece::BKing)));
	if (inBoard(x + 0, y + 1) && isWhite(pieces[toi(x + 0, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 0, y + 1), Piece::BKing)));
	if (inBoard(x + 1, y + 1) && isWhite(pieces[toi(x + 1, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 1), Piece::BKing)));
	if (inBoard(x + 1, y + 0) && isWhite(pieces[toi(x + 1, y + 0)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 0), Piece::BKing)));
	if (inBoard(x + 1, y - 1) && isWhite(pieces[toi(x + 1, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y - 1), Piece::BKing)));
	if (inBoard(x + 0, y - 1) && isWhite(pieces[toi(x + 0, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 0, y - 1), Piece::BKing)));
	if (inBoard(x - 1, y - 1) && isWhite(pieces[toi(x - 1, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y - 1), Piece::BKing)));
	if (inBoard(x - 1, y + 0) && isWhite(pieces[toi(x - 1, y + 0)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 0), Piece::BKing)));

	if (bCanCastleQ && pieces[1] == Piece::None && pieces[2] == Piece::None && pieces[3] == Piece::None) {
		outMoves.push_back(Move(Square(4, Piece::None), Square(2, Piece::BKing), Move::Castling::BQ));
	}
	if (bCanCastleK && pieces[5] == Piece::None && pieces[6] == Piece::None) {
		outMoves.push_back(Move(Square(4, Piece::None), Square(6, Piece::BKing), Move::Castling::BK));
	}
}
