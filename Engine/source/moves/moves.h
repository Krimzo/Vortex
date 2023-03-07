#pragma once

#include "board/board.h"


namespace vtx {
    void get_piece_moves(const board& board, int piece_index, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_pawn_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_pawn_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_knight_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_knight_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_bishop_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_bishop_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_rook_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_rook_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_queen_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_queen_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}

namespace vtx {
    void get_white_king_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
    void get_black_king_moves(const board& board, int x, int y, std::vector<vtx::board>& out_boards);
}
