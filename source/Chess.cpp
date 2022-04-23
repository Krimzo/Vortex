#include "Chess.h"


int main() {
	win.start = [&]() {
		//kl::console::hide();
		win.setIcon("resource/skull.ico");
		board.loadFen(Board::defaultFen);
	};
	win.update = [&]() {
		board.update(win, frame);
		board.draw(frame);
		win.drawImage(frame);
	};
	win.startNew(frame.size(), "Chess Engine", false, false);
}
