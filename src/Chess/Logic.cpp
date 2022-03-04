#include "Chess/Chess.h"


void Logic() {
	// Getting the square size
	const int squareSize = frame.width() / 8;

	// Getting the mouse click coords
	static bool lmbWasDown = false;
	if (win.mouse.lmb) {
		if (!lmbWasDown) {
			const kl::int2 clickedSqr = win.mouse.position / squareSize;
			const int clickedInd = clickedSqr.y * 8 + clickedSqr.x;

			// Piece select
			if (board.selected == -1) {
				if (board.pieces[clickedInd] != Piece::None) {
					board.selected = clickedInd;
				}
			}
			else {
				if (board.pieces[clickedInd] != Piece::None && clickedInd != board.selected) {
					board.selected = clickedInd;
				}
				else {
					board.selected = -1;
				}
			}
			
		}
		lmbWasDown = true;
	}
	else {
		lmbWasDown = false;
	}
}
