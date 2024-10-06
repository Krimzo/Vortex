#include "vortex.h"


vtx::Piece::Piece()
{}

vtx::Piece::Piece(const char type)
	: type(type)
{}

vtx::Piece::operator char() const
{
	return type;
}

bool vtx::Piece::is_white(const bool allow_none) const
{
	return (type > 64 && type < 91) || (allow_none && !type);
}

bool vtx::Piece::is_black(const bool allow_none) const
{
	return (type > 96 && type < 123) || (allow_none && !type);
}
