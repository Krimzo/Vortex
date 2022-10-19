#include "Board/Board.h"
#include "Engine/Engine.h"


static const kl::Color BoardColors[8] = {
	{ 240, 215, 180 },
	{ 180, 135, 100 },
	{ 180, 235, 240 },
	{ 100, 180, 175 },
	{ 205, 240, 175 },
	{ 145, 180, 95  },
	{ 240, 180, 175 },
	{ 170, 100, 90  },
};


Board::Board() {}

void Board::playPlayersTurn(kl::Window& window, int clickedIndex) {
	if (position.getWinState()) {
		return;
	}

	if (selectedSquare > -1) {
		kl::Vector<Position> positions;
		position.pieces[selectedSquare].getMoves(position, selectedSquare, positions);

		for (auto& position : positions) {
			if (clickedIndex == position.lastPlayedMove.y) {
				this->position = position;

				if (position.getWinState() > 0) {
					window.setTitle("Player wins!");
				}
				else {
					playEnginesTurn(window);
				}

				break;
			}
		}

		selectedSquare = -1;
	}
	else if (position.pieces[clickedIndex].isWhite()) {
		selectedSquare = clickedIndex;
	}
}

void Board::playEnginesTurn(kl::Window& window) {
	if (position.getWinState()) {
		return;
	}

	window.setTitle("Calculating..");

	Engine engine = {};
	position = engine.findBest(this->position, 6);

	kl::Print(std::fixed,
		"Search Depth: ", engine.getSearchDepth(),
		" | Time: ", engine.getSearchTime(),
		" | Calls: ", engine.getCallCount(),
		" | Eval: ", position.evaluation);

	if (position.getWinState() < 0) {
		window.setTitle("Engine wins!");
	}
	else {
		window.setTitle("Player's move");
	}
}

static void DrawSquare(kl::Image& target, int index, const kl::Color& lightColor, const kl::Color& darkColor) {
	const int squareSize = target.getWidth() / 8;
	const kl::Int2 position = { index % 8, index / 8 };
	target.drawRectangle(position * squareSize, (position + kl::Int2::Splash(1)) * squareSize - kl::Int2::Splash(1),
		((position.x % 2) == (position.y % 2)) ? lightColor : darkColor, true);
}

void Board::render(kl::Image& target) const {
	for (int i = 0; i < 64; i++) {
		if (i == selectedSquare) {
			DrawSquare(target, i, BoardColors[2], BoardColors[3]);
		}
		else {
			DrawSquare(target, i, BoardColors[0], BoardColors[1]);
		}
	}

	if (position.lastPlayedMove.x >= 0 && position.lastPlayedMove.y >= 0) {
		DrawSquare(target, position.lastPlayedMove.x, BoardColors[4], BoardColors[5]);
		DrawSquare(target, position.lastPlayedMove.y, BoardColors[4], BoardColors[5]);
	}

	if (selectedSquare >= 0) {
		kl::Vector<Position> positions;
		position.pieces[selectedSquare].getMoves(position, selectedSquare, positions);

		for (auto& position : positions) {
			DrawSquare(target, position.lastPlayedMove.y, BoardColors[2], BoardColors[3]);
		}
	}

	if (position.getWinState()) {
		DrawSquare(target, position.lastPlayedMove.y, BoardColors[6], BoardColors[7]);
	}

	for (int i = 0; i < 64; i++) {
		const kl::Image* icon = position.pieces[i].getIcon();
		if (icon) {
			target.drawImage(kl::Int2(i % 8, i / 8) * (target.getWidth() / 8), *icon);
		}
	}
}
