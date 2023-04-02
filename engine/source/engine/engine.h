#pragma once

#include "moves/moves.h"


namespace vtx {
	class engine
	{
		uint8_t search_depth_ = 0;
		std::atomic<uint64_t> call_count_ = 0;
		float search_time_ = 0.0f;

		board find_best_board(board& board, int depth, float alpha, float beta);
		board find_best_board_parallel(board& board, std::atomic<int> depth, std::atomic<float> alpha, std::atomic<float> beta);

		bool piece_type_check(const board& board, const piece& piece);

		bool evaluation_check(bool white_to_play, float& alpha, float& beta, const board& possible_board, board& best_board);
		bool evaluation_check_parallel(bool white_to_play, std::atomic<float>& alpha, std::atomic<float>& beta, const board& possible_board, board& best_board);

	public:
		engine();
		~engine();

		int get_search_depth() const;
		uint64_t get_call_count() const;
		float get_search_time() const;

		void static_evaluation(board& position);
		board find_best_board_init(board& position, int search_depth, bool parallel);
	};
}
