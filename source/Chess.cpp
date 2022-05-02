#include "Piece.h"
#include "Board.h"
#include "Engine.h"

static kl::window win;
static kl::image frame(kl::int2(800));
static Board board;


int main() {
	win.start = [&]() {
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
