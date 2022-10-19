#include "Board/Board.h"
#include "Engine/Engine.h"


int main() {
	Board board = {};
	board.position = Position(DefaultFEN);

	kl::Window window = { { 800, 800 }, "Chess Engine" };
	kl::DoubleBuffer frameBuffer = { window.getSize() };

	window.setResizeable(false);
	window.mouse.left.onPress = [&]() {
		kl::Int2 clickedSquare = window.mouse.getPosition() / (frameBuffer.getSize().x / 8);
		board.playPlayersTurn(window, clickedSquare.y * 8 + clickedSquare.x);
	};

	while (window.process()) {
		board.render(*frameBuffer.getBackBuffer());
		frameBuffer.drawToWindow(window);
		frameBuffer.swapBuffers();
	}
}
