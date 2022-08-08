#include "Board/Board.h"
#include "Engine/Engine.h"


int main() {
	kl::Window window = { { 800, 800 }, "Chengine" };
	kl::DoubleBuffer frameBuffer = { window.getSize() };
	Board board = {};

	board.loadFEN(Board::DefaultFEN);

	board.setSearchDisplay(false); // Set this to true for FUN :)

	window.setResizeable(false);

	window.mouse.left.onPress = [&]() {
		kl::Int2 clickedSquare = window.mouse.getPosition() / (frameBuffer.getSize().x / 8);
		board.playerPlay(window, Board::ToIndex(clickedSquare.x, clickedSquare.y));
	};

	while (window.process()) {
		board.drawToImage(*frameBuffer.getBackBuffer());
		frameBuffer.drawToWindow(window);
		frameBuffer.swapBuffers();
	}
}
