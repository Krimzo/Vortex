#include "BoardState.h"


BoardState::BoardState() {}
BoardState::BoardState(float eval) : eval(eval) {}
BoardState::BoardState(float eval, const Move& move) : eval(eval), move(move) {}
