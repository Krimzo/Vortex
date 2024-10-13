#include "vortex.h"


vtx::Game::Game(System& system)
    : system(system)
{
	reset();
}

void vtx::Game::update()
{
	if (!system.viewport_focused)
		return;

	auto& mouse = system.window.mouse;
	if (mouse.left.pressed()) {
		on_mouse_clicked();
	}
	else if (mouse.left.released()) {
		on_mouse_released();
	}
}

void vtx::Game::reset()
{
	board = { default_fen };
	search_results.clear();
	search_results.emplace_back(board, 0, 0.0f);
}

kl::Float2 vtx::Game::mouse_ndc() const
{
	const kl::Int2 board_position = get_board_position();
	const kl::Int2 board_size = get_board_size();
	const kl::Int2 current_position = system.window.mouse.position();

	kl::Int2 position_in_viewport = current_position - board_position;
	position_in_viewport.y = board_size.y - 1 - position_in_viewport.y;

	kl::Float2 ndc = (kl::Float2) position_in_viewport / (kl::Float2) board_size;
	ndc *= 2.0f;
	ndc -= kl::Float2(1.0f);
	return ndc;
}

void vtx::Game::on_mouse_clicked()
{
	const kl::Int2 clicked_square = get_mouse_square();
	const int clicked_index = clicked_square.x + clicked_square.y * 8;
	if (board[clicked_index].is_white()) {
		board.selected_square = clicked_index;
	}
}

void vtx::Game::on_mouse_released()
{
	if (board.selected_square < 0)
		return;

	kl::Int2 clicked_square = get_mouse_square();
	int released_index = clicked_square.to_index(8);
	if (play_players_turn(released_index)) {
		play_engines_turn();
	}
	board.selected_square = -1;
}

kl::Int2 vtx::Game::get_board_position() const
{
	const kl::Int2 viewport_size = system.viewport_size;
	kl::Int2 top_left = system.viewport_top_left;
	if (viewport_size.x > viewport_size.y) {
		top_left.x += (viewport_size.x - viewport_size.y) / 2;
	}
	else {
		top_left.y += (viewport_size.y - viewport_size.x) / 2;
	}
	return top_left;
}

kl::Int2 vtx::Game::get_board_size() const
{
	const kl::Int2 viewport_position = system.viewport_top_left;
	const kl::Int2 board_position = get_board_position();
	return system.viewport_size - (board_position - viewport_position) * 2;
}

kl::Int2 vtx::Game::get_mouse_square() const
{
	const kl::Int2 viewport_position = system.viewport_top_left;
	const kl::Int2 viewport_size = system.viewport_size;

	const kl::Int2 board_position = get_board_position();
	const int square_size = kl::min(viewport_size.x, viewport_size.y) / 8;

	kl::Int2 clicked_square = (system.window.mouse.position() - board_position);
	clicked_square /= square_size;
	return clicked_square;
}

bool vtx::Game::play_players_turn(const int destination_index)
{
	if (board.get_win_state() || board.selected_square < 0)
		return false;

	std::vector<Board> boards;
	get_piece_moves(board, board.selected_square, boards);
	for (const auto& board : boards) {
		if (destination_index == board.last_played_to) {
			this->board = board;
			return true;
		}
	}
	return false;
}

void vtx::Game::play_engines_turn()
{
	if (board.get_win_state())
		return;

	SearchResult result = engine.search(board, search_depth);
	search_results.push_back(result);
	board = result.board;
}
