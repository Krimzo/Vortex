#include "Chess/Chess.h"


void Update() {
	// Logic
	Logic();

	// Rendering pieces
	DrawBoard();

	// Frame display
	win.drawImage(frame);
}
