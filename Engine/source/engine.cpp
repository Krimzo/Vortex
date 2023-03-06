#include "board/board.h"
#include "engine/engine.h"


int main()
{
	piece::load_icon_textures();

	board board = {};
	board.position = position(default_fen);

	kl::window window = { { 800, 800 }, "Chess Engine" };
	auto frame_buffer = kl::frame_buffer(window.size());

	window.set_resizeable(false);
	window.mouse.left.on_press.push_back([&]
	{
		const kl::int2 clicked_square = window.mouse.position() / (int) (frame_buffer.size().x / 8);
		board.play_players_turn(window, clicked_square.y * 8 + clicked_square.x);
	});

	while (window.process()) {
		board.render(*frame_buffer.back_buffer());
		window.draw_image(frame_buffer.front_buffer());
		frame_buffer.swap();
	}
}
