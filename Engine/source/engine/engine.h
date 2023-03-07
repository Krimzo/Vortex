#pragma once

#include "moves/moves.h"


namespace vtx {
	class engine
	{
		int search_depth_ = 0;
		uint64_t call_count_ = 0;
		float search_time_ = 0.0f;

		board find_best_position(const board& board, int depth, float alpha, float beta);

	public:
		engine();
		virtual ~engine();

		int get_search_depth() const;
		uint64_t get_call_count() const;
		float get_search_time() const;

		float static_evaluation(const board& position);
		board find_best_position(const board& position, int search_depth);
	};
}
