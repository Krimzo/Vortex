#include "Chess/Chess.h"


void Logic() {
	// Engine plays
	if (!whiteToPlay) {
		// Getting the best data
		kl::time::interval();
		const BestInfo bestData = BestMoveMT(pieces);
		std::cout << "Elapsed time : " << kl::time::interval() << std::endl;

		// Updating title eval
		win.setTitle(std::to_string(int(bestData.eval)));

		// Checkmate test
		if (pieces[bestData.move.y] == Piece::WKing) {
			win.setTitle("Black wins!");
			win.update = []() {};
			wonSquare = bestData.move.y;
		}
		else if (pieces[bestData.move.y] == Piece::BKing) {
			win.setTitle("White wins!");
			win.update = []() {};
			wonSquare = bestData.move.y;
		}

		// Moving engine piece
		pieces[bestData.move.y] = pieces[bestData.move.x];
		pieces[bestData.move.x] = Piece::None;
		whiteToPlay = true;
	}

	// Getting the mouse click coords
	static bool lmbWasDown = false;
	const int squareSize = frame.width() / 8;
	if (win.mouse.lmb && wonSquare == -1) {
		if (!lmbWasDown) {
			const kl::int2 clickedSqr = win.mouse.position / squareSize;
			const int clickedInd = clickedSqr.y * 8 + clickedSqr.x;

			// Piece move
			if ([&]() {
				for (int pm : pieceMoves) {
					if (clickedInd == pm) {
						if (pieces[clickedInd] == Piece::WKing) {
							win.setTitle("Black wins!");
							win.update = [](){};
							wonSquare = clickedInd;
						}
						else if (pieces[clickedInd] == Piece::BKing) {
							win.setTitle("White wins!");
							win.update = []() {};
							wonSquare = clickedInd;
						}
						pieces[clickedInd] = pieces[selected];
						pieces[selected] = Piece::None;
						return true;
					}
				}
				return false;
			}()) {
				selected = -1;
				whiteToPlay = false;
			}

			// Piece select
			else if (pieces[clickedInd] != Piece::None && clickedInd != selected && (whiteToPlay && PieceColor(pieces[clickedInd]) > 0)) {
				selected = clickedInd;
			}
			else {
				selected = -1;
			}

			// Getting the possible moves
			pieceMoves = PieceMoves(pieces, selected);
		}
		lmbWasDown = true;
	}
	else {
		lmbWasDown = false;
	}
}
