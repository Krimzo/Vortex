#include "Position/Position.h"


bool InBoard(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int ToIndex(int x, int y) {
	return y * 8 + x;
}


Position::Position() {}

Position::Position(const FEN& fen) {
	loadFEN(fen);
}

void Position::loadFEN(const FEN& fen) {
	kl::Vector<kl::String> parts = kl::Strings::Split(fen, ' ');
	if (kl::Warning(parts.size() < 3, "Bad FEN data")) {
		return;
	}

	this->clear();

	whiteToPlay = (parts[1] == "w");

	for (int i = 0, position = 0; i < parts[0].size() && position < 64; i++) {
		const char lowerChar = tolower(fen[i]);
		if (lowerChar == 'p' || lowerChar == 'n' || lowerChar == 'b' || lowerChar == 'r' || lowerChar == 'q' || lowerChar == 'k') {
			pieces[position++] = Piece((PieceType) fen[i]);
		}
		else if (isdigit(fen[i])) {
			position += fen[i] - 48;
		}
	}

	for (int i = 0; i < parts[2].size(); i++) {
		switch (parts[2][i]) {
		case 'K':
			castlingWK = true;
			break;
		case 'Q':
			castlingWQ = true;
			break;
		case 'k':
			castlingBK = true;
			break;
		case 'q':
			castlingBQ = true;
			break;
		}
	}
}

void Position::clear() {
	evaluation = 0;
	for (auto& piece : pieces) {
		piece = {};
	}
	
	whiteToPlay = true;
	bool castlingWK = true;
	bool castlingWQ = true;
	bool castlingBK = true;
	bool castlingBQ = true;

	lastPlayedMove = kl::Int2::Splash(-1);
}

Position Position::afterPlaying(int fromIndex, int toIndex, PieceType newType) const {
	Position position = *this;

	if (position.pieces[fromIndex].type == PieceType::WKing) {
		position.castlingWK = false;
		position.castlingWQ = false;
	}

	if (position.pieces[fromIndex].type == PieceType::BKing) {
		position.castlingBK = false;
		position.castlingBQ = false;
	}

	if (position.pieces[fromIndex].type == PieceType::WRook) {
		if (fromIndex == 63) {
			position.castlingWK = false;
		}
		else if (fromIndex == 56) {
			position.castlingWQ = false;
		}
	}

	if (position.pieces[fromIndex].type == PieceType::BRook) {
		if (fromIndex == 7) {
			position.castlingBK = false;
		}
		else if (fromIndex == 0) {
			position.castlingBQ = false;
		}
	}

	position.lastPlayedMove.x = fromIndex;
	position.lastPlayedMove.y = toIndex;

	position.pieces[fromIndex].type = PieceType::None;
	position.pieces[toIndex].type = newType;

	position.whiteToPlay = !whiteToPlay;

	return position;
}

int Position::getWinState() const {
	int whiteKingCount = 0;
	int blackKingCount = 0;

	for (auto& piece : pieces) {
		if (piece.type == PieceType::WKing) {
			whiteKingCount += 1;
		}
		if (piece.type == PieceType::BKing) {
			blackKingCount += 1;
		}
	}

	return whiteKingCount - blackKingCount;
}
