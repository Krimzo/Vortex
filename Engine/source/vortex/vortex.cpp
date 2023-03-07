#include "vortex/vortex.h"


vortex::vortex()
{
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
		renderer_.resize(window_.size());
		renderer_.render(board_);

		window_.draw_image(renderer_);
		renderer_.swap();
	}
}

void vortex::on_mouse_click()
{
	if (!currently_calculating) {
		currently_calculating = true;

		kl::int2 clicked_square = (window_.mouse.position() - renderer_.start_top_left);
		clicked_square /= renderer_.square_size;

		play_players_turn(clicked_square.x + clicked_square.y * 8);
		window_.notify();

		currently_calculating = false;
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
			if (clicked_index == board.last_played_move.y) {
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
	board_ = engine_.find_best_position(board_, 5);

	kl::print(std::fixed,
		"Search Depth: ", engine_.get_search_depth(),
		" | Time: ", engine_.get_search_time(),
		" | Calls: ", engine_.get_call_count(),
		" | Eval: ", board_.evaluation);
	window_.set_title((board_.get_win_state() < 0) ? "Engine wins!" : "Player's move");
}
