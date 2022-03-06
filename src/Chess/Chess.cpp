#include "Chess/Chess.h"


int main() {
	//kl::console::hide();
	board.loadFen(Board::defaultFen);
	win.update = [&]() {
		// Logic
		board.update(win, frame);

		// Rendering pieces
		board.draw(frame);

		// Frame display
		win.drawImage(frame);
	};
	win.startNew(frame.size(), "Chess Engine", false, false);
}
