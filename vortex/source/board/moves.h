#pragma once

#include "board/board.h"


namespace vtx {
    void get_white_pawn_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_pawn_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
    void get_white_knight_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_knight_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
    void get_white_bishop_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_bishop_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
    void get_white_rook_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_rook_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
    void get_white_queen_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_queen_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
    void get_white_king_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
    void get_black_king_moves(const Board& board, int x, int y, std::vector<Board>& out_boards);
}

namespace vtx {
	inline void get_piece_moves(const Board& board, const int piece_index, std::vector<vtx::Board>& out_boards)
	{
		const int x = piece_index % 8;
		const int y = piece_index / 8;
		switch (board[piece_index].type)
		{
			case W_PAWN: get_white_pawn_moves(board, x, y, out_boards); break;
			case B_PAWN: get_black_pawn_moves(board, x, y, out_boards); break;
			case W_KNIGHT: get_white_knight_moves(board, x, y, out_boards); break;
			case B_KNIGHT: get_black_knight_moves(board, x, y, out_boards); break;
			case W_BISHOP: get_white_bishop_moves(board, x, y, out_boards); break;
			case B_BISHOP: get_black_bishop_moves(board, x, y, out_boards); break;
			case W_ROOK: get_white_rook_moves(board, x, y, out_boards); break;
			case B_ROOK: get_black_rook_moves(board, x, y, out_boards); break;
			case W_QUEEN: get_white_queen_moves(board, x, y, out_boards); break;
			case B_QUEEN: get_black_queen_moves(board, x, y, out_boards); break;
			case W_KING: get_white_king_moves(board, x, y, out_boards); break;
			case B_KING: get_black_king_moves(board, x, y, out_boards); break;
		}
	}
}
