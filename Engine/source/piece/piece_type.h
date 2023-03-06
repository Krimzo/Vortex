#pragma once

#include <cstdint>


using piece_type = uint8_t;

inline const piece_type none = 0;

inline const piece_type w_pawn = 'P';
inline const piece_type w_knight = 'N';
inline const piece_type w_bishop = 'B';
inline const piece_type w_rook = 'R';
inline const piece_type w_queen = 'Q';
inline const piece_type w_king = 'K';

inline const piece_type b_pawn = 'p';
inline const piece_type b_knight = 'n';
inline const piece_type b_bishop = 'b';
inline const piece_type b_rook = 'r';
inline const piece_type b_queen = 'q';
inline const piece_type b_king = 'k';
