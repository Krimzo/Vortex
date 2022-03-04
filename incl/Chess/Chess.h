#pragma once

#include "KrimzLib/KrimzLib.hpp"

#include "Chess/Board.h"


inline kl::window win;

inline kl::image frame(kl::int2(800));

inline Board board;

void Start();
void Update();
void Logic();
