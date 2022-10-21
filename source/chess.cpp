#include "board/board.h"
#include "engine/engine.h"


int main()
{
	board board = {};
	board.position = position(default_fen);

	kl::window window = { { 800, 800 }, "Chess Engine" };
	auto frame_buffer = kl::frame_buffer(window.size());

	window.set_resizeable(false);
	window.mouse.left.on_press = [&]
	{
		const kl::int2 clicked_square = window.mouse.position() / static_cast<int>(frame_buffer.size().x / 8);
		board.play_players_turn(window, clicked_square.y * 8 + clicked_square.x);
	};

	while (window.process()) {
		board.render(*frame_buffer.back_buffer());
		frame_buffer.display(window);
		frame_buffer.swap();
	}
}
