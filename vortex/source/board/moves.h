#pragma once

#include "board/board.h"


namespace vtx {
    void get_white_pawn_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_pawn_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
    void get_white_knight_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_knight_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
    void get_white_bishop_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_bishop_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
    void get_white_rook_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_rook_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
    void get_white_queen_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_queen_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
    void get_white_king_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
    void get_black_king_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator);
}

namespace vtx {
	inline void get_piece_moves(Board const& board, int piece_index, std::function<void(Board&)> const& board_iterator)
	{
		int x = piece_index % 8, y = piece_index / 8;
		switch (board[piece_index].type)
		{
		case W_PAWN: get_white_pawn_moves(board, x, y, board_iterator); break;
		case B_PAWN: get_black_pawn_moves(board, x, y, board_iterator); break;
		case W_KNIGHT: get_white_knight_moves(board, x, y, board_iterator); break;
		case B_KNIGHT: get_black_knight_moves(board, x, y, board_iterator); break;
		case W_BISHOP: get_white_bishop_moves(board, x, y, board_iterator); break;
		case B_BISHOP: get_black_bishop_moves(board, x, y, board_iterator); break;
		case W_ROOK: get_white_rook_moves(board, x, y, board_iterator); break;
		case B_ROOK: get_black_rook_moves(board, x, y, board_iterator); break;
		case W_QUEEN: get_white_queen_moves(board, x, y, board_iterator); break;
		case B_QUEEN: get_black_queen_moves(board, x, y, board_iterator); break;
		case W_KING: get_white_king_moves(board, x, y, board_iterator); break;
		case B_KING: get_black_king_moves(board, x, y, board_iterator); break;
		}
	}
}
