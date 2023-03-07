#include "vortex/vortex.h"


vortex::vortex()
{
	window_.mouse.left.on_press.push_back([&]
	{
		const int square_size = renderer_.get_square_size();
		const kl::int2 start_top_left = renderer_.get_start_top_left(square_size);
		const kl::int2 clicked_square = (window_.mouse.position() + start_top_left) / square_size;
		play_players_turn(clicked_square.x + clicked_square.y * 8);
	});
}

vortex::~vortex()
{}

void vortex::run()
{
	while (window_.process()) {
		renderer_.handle_resize(window_.size());
		renderer_.render(board_);

		window_.draw_image(renderer_);
		renderer_.swap();
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

	const std::string next_message = (board_.get_win_state() < 0) ? "Engine wins!" : "Player's move";
	window_.set_title(next_message);
}
