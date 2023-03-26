#include "engine/engine.h"


vtx::engine::engine()
{}

vtx::engine::~engine()
{}

int vtx::engine::get_search_depth() const
{
	return search_depth_;
}

uint64_t vtx::engine::get_call_count() const
{
	return call_count_;
}

float vtx::engine::get_search_time() const
{
	return search_time_;
}
