#include "Chess/Board.h"


// Icons
const kl::image Board::icons[16] = {
    kl::image("res/w_pawn.png"),
    kl::image("res/w_knight.png"),
    kl::image("res/w_bishop.png"),
    kl::image("res/w_rook.png"),
    kl::image("res/w_queen.png"),
    kl::image("res/w_king.png"),
    kl::image("res/b_pawn.png"),
    kl::image("res/b_knight.png"),
    kl::image("res/b_bishop.png"),
    kl::image("res/b_rook.png"),
    kl::image("res/b_queen.png"),
    kl::image("res/b_king.png")
};

// Loads fen data
const std::string Board::defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
void Board::loadFen(const std::string& fen) {
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

// Draws the board
void Board::draw() const {
    // Target check
    if (!frame) {
        return;
    }

    // Square size
    const int squareSize = frame->width() / 8;

	// Drawing the squares
	for (int i = 0; i < 64; i++) {
        const int x = i % 8;
        const int y = i / 8;
        if ((x % 2) == (y % 2)) {
            frame->drawRectangle(
                kl::int2(x * squareSize, y * squareSize),
                kl::int2(kl::int2((x + 1) * squareSize, (y + 1) * squareSize)),
                (i == selected) ? selectL : squareL,
                true);
        }
        else {
            frame->drawRectangle(
                kl::int2(x * squareSize, y * squareSize),
                kl::int2(kl::int2((x + 1) * squareSize, (y + 1) * squareSize)),
                (i == selected) ? selectD : squareD,
                true);
        }
	}

    // Drawing the pieces
    for (int i = 0; i < 64; i++) {
        if (pieces[i]) {
            const int x = i % 8;
            const int y = i / 8;
            frame->drawImage(kl::int2(x * squareSize, y * squareSize), Board::icons[pieces[i] - 1]);
        }
    }
}
