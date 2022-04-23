#include "Square.h"


Square::Square() : index(-1), piece(Piece::Type::None) {}
Square::Square(int index, Piece::Type piece) : index(index), piece(piece) {}
