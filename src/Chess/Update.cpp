#include "Chess/Chess.h"


void Update() {
	// Logic
	Logic();

	// Rendering pieces
	board.draw();

	// Frame display
	win.drawImage(frame);
}
