#include "Chess/Board.h"


// Loads fen data
void LoadFen(const std::string& fen) {
    // Splitting the fen by space
    std::vector<std::string> fenParts;
    std::stringstream fenStream(fen);
    for (std::string fenPart; std::getline(fenStream, fenPart, ' ');) {
        fenParts.push_back(fenPart);
    }

    // Fen parts check
    if (fenParts.size() < 3) {
        std::cout << "Bad fen input!";
        std::cin.get();
        exit(69);
    }

    // Loading the piece data
    int position = 0;
    for (int i = 0; i < fenParts[0].size() && position < 64; i++) {
        const char lowerChar = tolower(fen[i]);
        if (lowerChar == 'p' || lowerChar == 'n' || lowerChar == 'b' || lowerChar == 'r' || lowerChar == 'q' || lowerChar == 'k') {
            switch (fen[i]) {
            // White pieces
            case 'P':
                pieces[position] = Piece::WPawn;
                break;
            case 'N':
                pieces[position] = Piece::WKnight;
                break;
            case 'B':
                pieces[position] = Piece::WBishop;
                break;
            case 'R':
                pieces[position] = Piece::WRook;
                break;
            case 'Q':
                pieces[position] = Piece::WQueen;
                break;
            case 'K':
                pieces[position] = Piece::WKing;
                break;

            // Black pieces
            case 'p':
                pieces[position] = Piece::BPawn;
                break;           
            case 'n':            
                pieces[position] = Piece::BKnight;
                break;           
            case 'b':            
                pieces[position] = Piece::BBishop;
                break;           
            case 'r':            
                pieces[position] = Piece::BRook;
                break;           
            case 'q':            
                pieces[position] = Piece::BQueen;
                break;           
            case 'k':            
                pieces[position] = Piece::BKing;
                break;
            }
            position++;
        }
        else if (isdigit(fen[i])) {
            position += (fen[i] - 48);
        }
    }

    // Loading "to move"
    whiteToPlay = (fenParts[1] == "w");

    // Loading castling rules
    wCanCastleK = false;
    wCanCastleQ = false;
    bCanCastleK = false;
    bCanCastleQ = false;
    for (int i = 0; i < fenParts[2].size(); i++) {
        if (fenParts[2][i] == 'K') {
            wCanCastleK = true;
        }
        else if (fenParts[2][i] == 'Q') {
            wCanCastleQ = true;
        }
        else if (fenParts[2][i] == 'k') {
            bCanCastleK = true;
        }
        else if (fenParts[2][i] == 'q') {
            bCanCastleQ = true;
        }
    }
}

// Draws a square
void DrawSquare(int ind, const kl::color& colL, const kl::color& colD) {
    // Square size
    const int squareSize = frame.width() / 8;

    // Drawing
    const kl::int2 pos(ind % 8, ind / 8);
    frame.drawRectangle(
        pos * squareSize,
        (pos + 1) * squareSize - 1,
        (pos.x % 2) == (pos.y % 2) ? colL : colD,
        true);
}

// Draws the board
void DrawBoard() {
	// Drawing the squares
	for (int i = 0; i < 64; i++) {
        if (i == selected) {
            DrawSquare(i, selectL, selectD);
        }
        else {
            DrawSquare(i, squareL, squareD);
        }
	}

    // Drawing the moves
    if (selected > -1) {
        for (int pm : pieceMoves) {
            DrawSquare(pm, moveL, moveD);
        }
    }

    // Drawing the won square
    if (wonSquare > -1) {
        DrawSquare(wonSquare, wonL, wonD);
    }

    // Drawing the pieces
    const int squareSize = frame.width() / 8;
    for (int i = 0; i < 64; i++) {
        if (pieces[i] != Piece::None) {
            const kl::int2 pos(i % 8, i / 8);
            frame.drawImage(pos * squareSize, icons[pieces[i] - 1]);
        }
    }
}
