#include "piece/piece.h"


vtx::piece::piece()
{}

vtx::piece::piece(const char type)
	: type(type)
{}

vtx::piece::operator char() const
{
	return type;
}

bool vtx::piece::is_white(const bool allow_none) const
{
	return (type > 64 && type < 91) || (allow_none && !type);
}

bool vtx::piece::is_black(const bool allow_none) const
{
	return (type > 96 && type < 123) || (allow_none && !type);
}
