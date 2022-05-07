#include "Types/Piece.h"
#include "Board/Board.h"
#include "Engine/Engine.h"


static kl::window win;
static kl::double_buffer fbuffer(kl::int2(800));
static Board board;

int main() {
	win.mouse.lmb.press = [&]() {
		if (board.whiteToPlay && board.wonSquare < 0) {
			const kl::int2 clickedSqr = win.mouse.position / (fbuffer.size().x / 8);
			const int clickedInd = Board::toi(clickedSqr.x, clickedSqr.y);

			// Piece move
			if (board.selectedSquare > -1) {
				std::vector<Move> moves;
				board.getMoves(board.selectedSquare, moves);
				for (auto& m : moves) {
					if (clickedInd == m.to.index) {
						// Checkmate test
						if (board.pieces[clickedInd] == Piece::BKing) {
							win.setTitle("Player wins!");
							board.wonSquare = clickedInd;
						}

						// Moving player piece
						board.playMove(m);
						board.whiteToPlay = false;
						break;
					}
				}
				board.selectedSquare = -1;
			}
			else if (Board::isWhite(board.pieces[clickedInd])) {
				board.selectedSquare = clickedInd;
			}
		}
	};
	win.start = [&]() {
		board.loadFen(Board::defaultFen);
		std::thread([&]() {
			while (board.wonSquare < 0) {
				board.update(win);
			}
		}).detach();
	};
	win.update = [&]() {
		board.draw(fbuffer.getBB());
		fbuffer >> win;
		fbuffer.swap();
	};
	win.startNew(fbuffer.size(), "Chess Engine", false, true);
}
