#include "Chess/Chess.h"


int main() {
	LoadFen(defaultFen);
	win.update = Update;
	win.startNew(frame.size(), "Chess Engine", false, false);
}
