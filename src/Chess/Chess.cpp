#include "Chess/Chess.h"


int main() {
	win.start = [&]() {
		//kl::console::hide();
		win.setIcon("res/skull.ico");
		board.loadFen(Board::defaultFen);
	};
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
