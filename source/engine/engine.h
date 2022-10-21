#pragma once

#include "position/position.h"


class engine
{
	int search_depth_ = 0;
	uint64_t call_count_ = 0;
	float search_time_ = 0.0f;

	position find_best_position(const position& position, int depth, float alpha, float beta);

public:
	engine();

	[[nodiscard]] int get_search_depth() const;
	[[nodiscard]] uint64_t get_call_count() const;
	[[nodiscard]] float get_search_time() const;

	static float static_evaluation(const position& position);
	position find_best_position(const position& position, int search_depth);
};
