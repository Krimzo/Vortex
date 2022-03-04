#include "Chess/Chess.h"


void Update() {
	// Clearing the frame
	//frame.fill(kl::colors::gray);

	// Rendering pieces
	frame.spixel(win.mouse.position, kl::colors::white);

	// Frame display
	win.drawImage(frame);
}
