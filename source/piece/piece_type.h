#pragma once

#include <cstdint>


using piece_type = uint8_t;

inline static constexpr piece_type none = 0;

inline static constexpr piece_type w_pawn = 'P';
inline static constexpr piece_type w_knight = 'N';
inline static constexpr piece_type w_bishop = 'B';
inline static constexpr piece_type w_rook = 'R';
inline static constexpr piece_type w_queen = 'Q';
inline static constexpr piece_type w_king = 'K';

inline static constexpr piece_type b_pawn = 'p';
inline static constexpr piece_type b_knight = 'n';
inline static constexpr piece_type b_bishop = 'b';
inline static constexpr piece_type b_rook = 'r';
inline static constexpr piece_type b_queen = 'q';
inline static constexpr piece_type b_king = 'k';
