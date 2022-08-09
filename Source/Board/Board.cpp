#include "Board/Board.h"
#include "Engine/Engine.h"


const kl::String Board::DefaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const kl::Color Board::defaultLight = { 240, 215, 180 };
const kl::Color Board::defaultDark = { 180, 135, 100 };
const kl::Color Board::selectedLigt = { 180, 235, 240 };
const kl::Color Board::selectedDark = { 100, 180, 175 };
const kl::Color Board::lastMoveLight = { 205, 240, 175 };
const kl::Color Board::lastMoveDark = { 145, 180, 95 };
const kl::Color Board::wonSquareLigt = { 240, 180, 175 };
const kl::Color Board::wonSquareDark = { 170, 100, 90 };

const kl::Image Board::icons[] = {
	{ "resource/w_pawn.png" },
	{ "resource/w_knight.png" },
	{ "resource/w_bishop.png" },
	{ "resource/w_rook.png" },
	{ "resource/w_queen.png" },
	{ "resource/w_king.png" },
	{ "resource/b_pawn.png" },
	{ "resource/b_knight.png" },
	{ "resource/b_bishop.png" },
	{ "resource/b_rook.png" },
	{ "resource/b_queen.png" },
	{ "resource/b_king.png" }
};


Board::Board() {}

Board::Board(const Board& board) {
	*this = board;
}

Board& Board::operator=(const Board& board) {
	m_MovePlaying = board.m_MovePlaying.load();

	m_SelectedSquare = board.m_SelectedSquare;
	m_WonSquare = board.m_WonSquare;
	m_LastMove = board.m_LastMove;

	m_WhiteToPlay = board.m_WhiteToPlay;

	for (int i = 0; i < 4; i++) {
		m_CastleRights[i] = board.m_CastleRights[i];
	}

	for (int i = 0; i < 64; i++) {
		m_Pieces[i] = board.m_Pieces[i];
	}

	return *this;
}

Piece Board::getPiece(int index) const {
	return m_Pieces[index];
}

void Board::clearPieces() {
	for (auto& piece : m_Pieces) {
		piece = Piece::None;
	}
}

void Board::loadFEN(const kl::String& fen) {
	clearPieces();

	kl::Vector<kl::String> parts = kl::Strings::Split(fen, ' ');

	if (kl::Warning(parts.size() < 3, "Bad fen data")) {
		return;
	}

	for (int i = 0, position = 0; i < parts[0].size() && position < 64; i++) {
		const char lowerChar = tolower(fen[i]);
		if (lowerChar == 'p' || lowerChar == 'n' || lowerChar == 'b' || lowerChar == 'r' || lowerChar == 'q' || lowerChar == 'k') {
			switch (fen[i]) {
			case 'P':
				m_Pieces[position] = Piece::WPawn;
				break;
			case 'N':
				m_Pieces[position] = Piece::WKnight;
				break;
			case 'B':
				m_Pieces[position] = Piece::WBishop;
				break;
			case 'R':
				m_Pieces[position] = Piece::WRook;
				break;
			case 'Q':
				m_Pieces[position] = Piece::WQueen;
				break;
			case 'K':
				m_Pieces[position] = Piece::WKing;
				break;

			case 'p':
				m_Pieces[position] = Piece::BPawn;
				break;
			case 'n':
				m_Pieces[position] = Piece::BKnight;
				break;
			case 'b':
				m_Pieces[position] = Piece::BBishop;
				break;
			case 'r':
				m_Pieces[position] = Piece::BRook;
				break;
			case 'q':
				m_Pieces[position] = Piece::BQueen;
				break;
			case 'k':
				m_Pieces[position] = Piece::BKing;
				break;
			}
			position++;
		}
		else if (isdigit(fen[i])) {
			position += fen[i] - 48;
		}
	}

	m_WhiteToPlay = parts[1] == "w";

	for (auto& right : m_CastleRights) {
		right = false;
	}

	for (int i = 0; i < parts[2].size(); i++) {
		if (parts[2][i] == 'K') {
			m_CastleRights[0] = true;
		}
		else if (parts[2][i] == 'Q') {
			m_CastleRights[1] = true;
		}
		else if (parts[2][i] == 'k') {
			m_CastleRights[2] = true;
		}
		else if (parts[2][i] == 'q') {
			m_CastleRights[3] = true;
		}
	}
}

void Board::playMove(const Move& move) {
	m_Pieces[move.from.index] = move.from.piece;
	m_Pieces[move.to.index] = move.to.piece;

	switch (move.castling) {
	case Castling::WQ:
		m_Pieces[56] = Piece::None;
		m_Pieces[59] = Piece::WRook;
		break;

	case Castling::WK:
		m_Pieces[63] = Piece::None;
		m_Pieces[61] = Piece::WRook;
		break;

	case Castling::BQ:
		m_Pieces[0] = Piece::None;
		m_Pieces[3] = Piece::BRook;
		break;

	case Castling::BK:
		m_Pieces[7] = Piece::None;
		m_Pieces[5] = Piece::BRook;
		break;
	}

	if (move.to.piece == Piece::WKing) {
		m_CastleRights[0] = false;
		m_CastleRights[1] = false;
	}
	else if (move.to.piece == Piece::BKing) {
		m_CastleRights[2] = false;
		m_CastleRights[3] = false;
	}
	else if (move.to.piece == Piece::WRook) {
		if (move.from.index == 56) {
			m_CastleRights[0] = false;
		}
		else if (move.from.index == 63) {
			m_CastleRights[1] = false;
		}
	}
	else if (move.to.piece == Piece::BRook) {
		if (move.from.index == 0) {
			m_CastleRights[2] = false;
		}
		else if (move.from.index == 7) {
			m_CastleRights[3] = false;
		}
	}

	m_LastMove = move;
	m_WhiteToPlay = !m_WhiteToPlay;
}

void Board::setSearchDisplay(bool state) {
	m_SearchDiplay = state;
}

void Board::playerPlay(kl::Window& window, int clickedIndex) {
	if (!m_MovePlaying && m_WonSquare < 0) {
		m_MovePlaying = true;

		if (m_SelectedSquare > -1) {
			kl::Vector<Move> moves;
			getSquareMoves(m_SelectedSquare, moves);

			for (auto& move : moves) {
				if (clickedIndex == move.to.index) {
					bool playerWon = false;

					if (m_Pieces[clickedIndex] == Piece::BKing) {
						window.setTitle("Player wins!");
						m_WonSquare = clickedIndex;
						playerWon = true;
					}

					playMove(move);

					if (!playerWon) {
						m_MovePlaying = false;
						kl::Thread([&]() {
							enginePlay(window);
						}).detach();
					}
					break;
				}
			}

			m_SelectedSquare = -1;
		}
		else if (Board::IsWhite(m_Pieces[clickedIndex])) {
			m_SelectedSquare = clickedIndex;
		}

		m_MovePlaying = false;
	}
}

void Board::enginePlay(kl::Window& window) {
	if (!m_MovePlaying && m_WonSquare < 0) {
		m_MovePlaying = true;

		window.setTitle("Calculating..");

		Engine engine = {};
		BoardInfo info = engine.search(*this, 6, m_SearchDiplay);

		kl::Print(std::fixed,
			"Search Depth: ", engine.getSearchDepth(),
			" | Time: ", engine.getSearchTime(),
			" | Calls: ", engine.getCallCount(),
			" | Eval: ", info.evaluation);

		window.setTitle("Player's move");

		if (info.bestMove.to.index >= 0 && m_Pieces[info.bestMove.to.index] == Piece::WKing) {
			window.setTitle("Engine wins!");
			m_WonSquare = info.bestMove.to.index;
		}

		playMove(info.bestMove);

		window.notify();

		m_MovePlaying = false;
	}
}

static void DrawSquare(kl::Image& target, int index, const kl::Color& lightColor, const kl::Color& darkColor) {
	const int squareSize = target.getWidth() / 8;
	const kl::Int2 position = { index % 8, index / 8 };
	target.drawRectangle(position * squareSize, (position + kl::Int2(1, 1)) * squareSize - kl::Int2(1, 1),
		(position.x % 2) == (position.y % 2) ? lightColor : darkColor, true);
}

void Board::drawToImage(kl::Image& target) const {
	for (int i = 0; i < 64; i++) {
		if (i == m_SelectedSquare) {
			DrawSquare(target, i, selectedLigt, selectedDark);
		}
		else {
			DrawSquare(target, i, defaultLight, defaultDark);
		}
	}

	if (m_LastMove.to.index >= 0) {
		DrawSquare(target, m_LastMove.from.index, lastMoveLight, lastMoveDark);
		DrawSquare(target, m_LastMove.to.index, lastMoveLight, lastMoveDark);
	}

	if (m_SelectedSquare >= 0) {
		kl::Vector<Move> moves;
		getSquareMoves(m_SelectedSquare, moves);
		for (auto& move : moves) {
			DrawSquare(target, move.to.index, selectedLigt, selectedDark);
		}
	}

	if (m_WonSquare >= 0) {
		DrawSquare(target, m_WonSquare, wonSquareLigt, wonSquareDark);
	}

	for (int i = 0; i < 64; i++) {
		const kl::Int2 position = kl::Int2(i % 8, i / 8) * (target.getWidth() / 8);

		switch (m_Pieces[i]) {
		case Piece::WPawn:
			target.drawImage(position, icons[0]);
			break;
		case Piece::WKnight:
			target.drawImage(position, icons[1]);
			break;
		case Piece::WBishop:
			target.drawImage(position, icons[2]);
			break;
		case Piece::WRook:
			target.drawImage(position, icons[3]);
			break;
		case Piece::WQueen:
			target.drawImage(position, icons[4]);
			break;
		case Piece::WKing:
			target.drawImage(position, icons[5]);
			break;

		case Piece::BPawn:
			target.drawImage(position, icons[6]);
			break;
		case Piece::BKnight:
			target.drawImage(position, icons[7]);
			break;
		case Piece::BBishop:
			target.drawImage(position, icons[8]);
			break;
		case Piece::BRook:
			target.drawImage(position, icons[9]);
			break;
		case Piece::BQueen:
			target.drawImage(position, icons[10]);
			break;
		case Piece::BKing:
			target.drawImage(position, icons[11]);
			break;
		}
	}
}
