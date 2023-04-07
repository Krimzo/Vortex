#include "vortex/vortex.h"


vortex::vortex()
{
	window_.on_resize.push_back([&](kl::int2 new_size)
	{
		renderer_.resize(new_size);
	});
	window_.keyboard.f.on_press.push_back([&]
	{
		white_is_bottom = !white_is_bottom;
	});
	window_.mouse.left.on_press.push_back([&]
	{
		std::thread(&vortex::on_mouse_click, this).detach();
	});
}

vortex::~vortex()
{}

void vortex::run()
{
	while (window_.process()) {
		renderer_.clear();
		renderer_.render(board_, white_is_bottom);
		renderer_.swap();
	}
}

void vortex::on_mouse_click()
{
	if (!currently_calculating_) {
		currently_calculating_ = true;

		const int square_size = min(window_.width(), window_.height()) / 8;
		const int full_board_size = (square_size * 8);
		const kl::int2 start_top_left = {
			(window_.width() - full_board_size) / 2,
			(window_.height() - full_board_size) / 2,
		};

		kl::int2 clicked_square = (window_.mouse.position() - start_top_left);
		clicked_square /= square_size;

		if (!white_is_bottom) {
			clicked_square = kl::int2(7) - clicked_square;
		}

		play_players_turn(clicked_square.x + clicked_square.y * 8);
		window_.notify();

		currently_calculating_ = false;
	}
}

void vortex::play_players_turn(const int clicked_index)
{
	if (board_.get_win_state()) {
		return;
	}

	if (board_.selected_square > -1) {
		std::vector<vtx::board> boards = {};
		vtx::get_piece_moves(board_, board_.selected_square, boards);

		for (auto& board : boards) {
			if (clicked_index == board.last_played_to) {
				board_ = board;

				if (board.get_win_state() > 0) {
					window_.set_title("Player wins!");
				}
				else {
					play_engines_turn();
				}
				break;
			}
		}

		board_.selected_square = -1;
	}
	else if (board_[clicked_index].is_white()) {
		board_.selected_square = clicked_index;
	}
}

void vortex::play_engines_turn()
{
	if (board_.get_win_state()) {
		return;
	}

	window_.set_title("Calculating..");
	board_ = engine_.find_best_board_init(board_, search_depth, parallel_search);

	kl::print(std::fixed,
		"Search Depth: ", engine_.get_search_depth(),
		" | Time: ", engine_.get_search_time(),
		" | Calls: ", engine_.get_call_count(),
		" | Eval: ", board_.evaluation);
	window_.set_title((board_.get_win_state() < 0) ? "Engine wins!" : "Player's move");
}
