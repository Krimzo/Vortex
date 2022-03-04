#include "Chess/Chess.h"


void Start() {
	// Binding the render target
	board.frame = &frame;

	// Loading default fen
	board.loadFen(Board::defaultFen);
}
