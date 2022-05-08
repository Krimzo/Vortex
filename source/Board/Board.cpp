#include "Board/Board.h"
#include "Engine/Engine.h"


Board::Board() {}
Board::Board(const Board& obj) {
	selectedSquare = obj.selectedSquare;
	wonSquare = obj.wonSquare;
	lastMove = obj.lastMove;
	whiteToPlay = obj.whiteToPlay.load();
	wCanCastleK = obj.wCanCastleK;
	wCanCastleQ = obj.wCanCastleQ;
	bCanCastleK = obj.bCanCastleK;
	bCanCastleQ = obj.bCanCastleQ;
	memcpy(pieces, obj.pieces, sizeof(pieces));
}

void Board::clear() {
	for (auto& piece : pieces) {
		piece = Piece::None;
	}
}

// Loads fen data
const std::string Board::defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
void Board::loadFen(const std::string& fen) {
	// Board clearing
	clear();

	// Splitting the fen by space
	std::vector<std::string> fenParts;
	std::stringstream fenStream(fen);
	for (std::string fenPart; std::getline(fenStream, fenPart, ' ');) {
		fenParts.push_back(fenPart);
	}

	// Fen parts check
	if (fenParts.size() < 3) {
		std::cout << "Bad fen input!";
		std::cin.get();
		exit(69);
	}

	// Loading the piece data
	int position = 0;
	for (int i = 0; i < fenParts[0].size() && position < 64; i++) {
		const char lowerChar = tolower(fen[i]);
		if (lowerChar == 'p' || lowerChar == 'n' || lowerChar == 'b' || lowerChar == 'r' || lowerChar == 'q' || lowerChar == 'k') {
			switch (fen[i]) {
				// White pieces
			case 'P':
				pieces[position] = Piece::WPawn;
				break;
			case 'N':
				pieces[position] = Piece::WKnight;
				break;
			case 'B':
				pieces[position] = Piece::WBishop;
				break;
			case 'R':
				pieces[position] = Piece::WRook;
				break;
			case 'Q':
				pieces[position] = Piece::WQueen;
				break;
			case 'K':
				pieces[position] = Piece::WKing;
				break;

				// Black pieces
			case 'p':
				pieces[position] = Piece::BPawn;
				break;
			case 'n':
				pieces[position] = Piece::BKnight;
				break;
			case 'b':
				pieces[position] = Piece::BBishop;
				break;
			case 'r':
				pieces[position] = Piece::BRook;
				break;
			case 'q':
				pieces[position] = Piece::BQueen;
				break;
			case 'k':
				pieces[position] = Piece::BKing;
				break;
			}
			position++;
		}
		else if (isdigit(fen[i])) {
			position += (fen[i] - 48);
		}
	}

	// Loading "to move"
	whiteToPlay = (fenParts[1] == "w");

	// Loading castling rules
	wCanCastleK = false;
	wCanCastleQ = false;
	bCanCastleK = false;
	bCanCastleQ = false;
	for (int i = 0; i < fenParts[2].size(); i++) {
		if (fenParts[2][i] == 'K') {
			wCanCastleK = true;
		}
		else if (fenParts[2][i] == 'Q') {
			wCanCastleQ = true;
		}
		else if (fenParts[2][i] == 'k') {
			bCanCastleK = true;
		}
		else if (fenParts[2][i] == 'q') {
			bCanCastleQ = true;
		}
	}
}

// Plays the move
void Board::playMove(const Move& move) {
	// Setting piece types
	pieces[move.from.index] = move.from.piece;
	pieces[move.to.index] = move.to.piece;

	// Castling rooks
	switch (move.castling) {
	case Move::Castling::WQ:
		pieces[56] = Piece::None;
		pieces[59] = Piece::WRook;
		break;
	case Move::Castling::WK:
		pieces[63] = Piece::None;
		pieces[61] = Piece::WRook;
		break;
	case Move::Castling::BQ:
		pieces[0] = Piece::None;
		pieces[3] = Piece::BRook;
		break;
	case Move::Castling::BK:
		pieces[7] = Piece::None;
		pieces[5] = Piece::BRook;
		break;
	}

	// Castling rights
	if (move.to.piece == Piece::WKing) {
		wCanCastleK = false;
		wCanCastleQ = false;
	}
	else if (move.to.piece == Piece::BKing) {
		bCanCastleK = false;
		bCanCastleQ = false;
	}
	else if (move.to.piece == Piece::WRook) {
		if (move.from.index == 56) {
			wCanCastleQ = false;
		}
		else if (move.from.index == 63) {
			wCanCastleK = false;
		}
	}
	else if (move.to.piece == Piece::BRook) {
		if (move.from.index == 0) {
			bCanCastleQ = false;
		}
		else if (move.from.index == 7) {
			bCanCastleK = false;
		}
	}

	// Saving last move
	lastMove = move;
}

// Engine play
void Board::update(kl::window& win) {
	// Engine plays
	if (!whiteToPlay) {
		// Updating title
		win.setTitle("Calculating..");

		// Resetting info
		Engine::calls = 0;
		Engine::timer.reset();

		// Getting the engine info
		const Info engineInfo = Engine::BestMove(*this, false, 0, -INFINITY, INFINITY);

		// Info
		std::cout << std::fixed << "Search Depth: " << Engine::SearchDepth << " | Time: " << Engine::timer.elapsed() << " | Calls: " << Engine::calls << " | Eval: " << engineInfo.eval << std::endl;

		// Title
		win.setTitle("Player's move");

		// Checkmate test
		if (pieces[engineInfo.bestMove.to.index] == Piece::WKing) {
			win.setTitle("Engine wins!");
			wonSquare = engineInfo.bestMove.to.index;
		}

		// Moving engine piece
		playMove(engineInfo.bestMove);
		whiteToPlay = true;
		win.notify();
	}
	Sleep(1);
}

// Draws a square
void DrawSquare(kl::image* target, int ind, const kl::color& colL, const kl::color& colD) {
	// Square size
	const int squareSize = target->width() / 8;

	// Drawing
	const kl::int2 pos(ind % 8, ind / 8);
	target->drawRectangle(pos * squareSize, (pos + 1) * squareSize - 1, (pos.x % 2) == (pos.y % 2) ? colL : colD, true);
}

// Draws the board
const kl::color squareL = kl::color(240, 215, 180);
const kl::color squareD = kl::color(180, 135, 100);
const kl::color selectL = kl::color(135, 225, 205);
const kl::color selectD = kl::color(75, 170, 150);
const kl::color lastL = kl::color(205, 210, 105);
const kl::color lastD = kl::color(170, 160, 60);
const kl::color wonL = kl::color(170, 20, 20);
const kl::color wonD = kl::color(160, 10, 10);
const kl::image icons[12] = {
	kl::image("resource/w_pawn.png"),
	kl::image("resource/w_knight.png"),
	kl::image("resource/w_bishop.png"),
	kl::image("resource/w_rook.png"),
	kl::image("resource/w_queen.png"),
	kl::image("resource/w_king.png"),
	kl::image("resource/b_pawn.png"),
	kl::image("resource/b_knight.png"),
	kl::image("resource/b_bishop.png"),
	kl::image("resource/b_rook.png"),
	kl::image("resource/b_queen.png"),
	kl::image("resource/b_king.png")
};
void Board::draw(kl::image* target) const {
	// Drawing the squares
	for (int i = 0; i < 64; i++) {
		if (i == selectedSquare) {
			DrawSquare(target, i, selectL, selectD);
		}
		else {
			DrawSquare(target, i, squareL, squareD);
		}
	}

	// Drawing the last move
	if (lastMove.to.index != -1) {
		DrawSquare(target, lastMove.from.index, lastL, lastD);
		DrawSquare(target, lastMove.to.index, lastL, lastD);
	}

	// Drawing the moves
	if (selectedSquare > -1) {
		std::vector<Move> moves;
		getMoves(selectedSquare, moves);
		for (auto& m : moves) {
			DrawSquare(target, m.to.index, selectL, selectD);
		}
	}

	// Drawing the won square
	if (wonSquare > -1) {
		DrawSquare(target, wonSquare, wonL, wonD);
	}

	// Drawing the pieces
	const int squareSize = target->width() / 8;
	for (int i = 0; i < 64; i++) {
		const kl::int2 squarePosition(i % 8, i / 8);
		switch (pieces[i]) {
		case Piece::WPawn:
			target->drawImage(squarePosition * squareSize, icons[0]);
			break;
		case Piece::WKnight:
			target->drawImage(squarePosition * squareSize, icons[1]);
			break;
		case Piece::WBishop:
			target->drawImage(squarePosition * squareSize, icons[2]);
			break;
		case Piece::WRook:
			target->drawImage(squarePosition * squareSize, icons[3]);
			break;
		case Piece::WQueen:
			target->drawImage(squarePosition * squareSize, icons[4]);
			break;
		case Piece::WKing:
			target->drawImage(squarePosition * squareSize, icons[5]);
			break;

		case Piece::BPawn:
			target->drawImage(squarePosition * squareSize, icons[6]);
			break;
		case Piece::BKnight:
			target->drawImage(squarePosition * squareSize, icons[7]);
			break;
		case Piece::BBishop:
			target->drawImage(squarePosition * squareSize, icons[8]);
			break;
		case Piece::BRook:
			target->drawImage(squarePosition * squareSize, icons[9]);
			break;
		case Piece::BQueen:
			target->drawImage(squarePosition * squareSize, icons[10]);
			break;
		case Piece::BKing:
			target->drawImage(squarePosition * squareSize, icons[11]);
			break;
		}
	}
}
