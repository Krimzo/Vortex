#include "Chess/Board.h"

#include "Chess/Engine.h"


// Piece icons
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

// Board colors
kl::color Board::squareL = kl::color(240, 215, 180);
kl::color Board::squareD = kl::color(180, 135, 100);
kl::color Board::selectL = kl::color(135, 225, 205);
kl::color Board::selectD = kl::color(75, 170, 150);
kl::color Board::lastL = kl::color(205, 210, 105);
kl::color Board::lastD = kl::color(170, 160, 60);
kl::color Board::wonL = kl::color(170, 20, 20);
kl::color Board::wonD = kl::color(160, 10, 10);

// Constructor
Board::Board() {
    this->pieces.resize(64);
}

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
                pieces[position] = Piece::Type::WPawn;
                break;
            case 'N':
                pieces[position] = Piece::Type::WKnight;
                break;
            case 'B':
                pieces[position] = Piece::Type::WBishop;
                break;
            case 'R':
                pieces[position] = Piece::Type::WRook;
                break;
            case 'Q':
                pieces[position] = Piece::Type::WQueen;
                break;
            case 'K':
                pieces[position] = Piece::Type::WKing;
                break;

            // Black pieces
            case 'p':
                pieces[position] = Piece::Type::BPawn;
                break;           
            case 'n':            
                pieces[position] = Piece::Type::BKnight;
                break;           
            case 'b':            
                pieces[position] = Piece::Type::BBishop;
                break;           
            case 'r':            
                pieces[position] = Piece::Type::BRook;
                break;           
            case 'q':            
                pieces[position] = Piece::Type::BQueen;
                break;           
            case 'k':            
                pieces[position] = Piece::Type::BKing;
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

// Plays the move
void Board::playMove(const Move& move) {
    pieces[move.from.index].type = move.from.piece;
    pieces[move.to.index].type = move.to.piece;
}

// Logic and input
void Board::update(kl::window& win, kl::image& target) {
    // Engine plays
    if (!whiteToPlay) {
        // Getting the engine info
        const BestInfo engineInfo = Engine::BestMove(*this);

        // Updating title eval
        win.setTitle(std::to_string(int(engineInfo.eval)));

        // Checkmate test
        if (pieces[engineInfo.move.to.index].type == Piece::Type::WKing) {
            win.setTitle("Black wins!");
            win.update = []() {};
            wonSqr = engineInfo.move.to.index;
        }

        // Moving engine piece
        playMove(engineInfo.move);
        lastMove = engineInfo.move;
        whiteToPlay = true;
    }

    // Getting the mouse click coords
    static bool lmbWasDown = false;
    if (win.mouse.lmb && wonSqr == -1) {
        if (!lmbWasDown) {
            const kl::int2 clickedSqr = win.mouse.position / (target.width() / 8);
            const int clickedInd = clickedSqr.y * 8 + clickedSqr.x;

            // Piece move
            if ([&]() {
                for (const Move& m : moves) {
                    if (clickedInd == m.to.index) {
                        // Checkmate test
                        if (pieces[clickedInd].type == Piece::Type::BKing) {
                            win.setTitle("White wins!");
                            win.update = []() {};
                            wonSqr = clickedInd;
                        }

                        // Moving player piece
                        playMove(m);
                        lastMove = m;
                        return true;
                    }
                }
                return false;
                }()) {
                selecSqr = -1;
                whiteToPlay = false;
            }

            // Piece select
            else if (pieces[clickedInd].type != Piece::Type::None && clickedInd != selecSqr && (whiteToPlay && pieces[clickedInd].color() > 0)) {
                selecSqr = clickedInd;
            }
            else {
                selecSqr = -1;
            }

            // Getting the possible moves
            moves = getMoves(selecSqr);
        }
        lmbWasDown = true;
    }
    else {
        lmbWasDown = false;
    }
}

// Draws a square
void DrawSquare(kl::image& target, int ind, const kl::color& colL, const kl::color& colD) {
    // Square size
    const int squareSize = target.width() / 8;

    // Drawing
    const kl::int2 pos(ind % 8, ind / 8);
    target.drawRectangle(
        pos * squareSize,
        (pos + 1) * squareSize - 1,
        (pos.x % 2) == (pos.y % 2) ? colL : colD,
        true);
}

// Draws the board
void Board::draw(kl::image& target) const {
	// Drawing the squares
	for (int i = 0; i < 64; i++) {
        if (i == selecSqr) {
            DrawSquare(target, i, selectL, selectD);
        }
        else {
            DrawSquare(target, i, squareL, squareD);
        }
	}

    // Drawing the last move
    if (lastMove.to.index != -1) {
        DrawSquare(target, lastMove.from.index, lastL, lastD);
        DrawSquare(target, lastMove.to.index, lastL, lastD);
    }

    // Drawing the moves
    if (selecSqr > -1) {
        for (const Move& m : moves) {
            DrawSquare(target, m.to.index, selectL, selectD);
        }
    }

    // Drawing the won square
    if (wonSqr > -1) {
        DrawSquare(target, wonSqr, wonL, wonD);
    }

    // Drawing the pieces
    const int squareSize = target.width() / 8;
    for (int i = 0; i < 64; i++) {
        if (pieces[i].type != Piece::Type::None) {
            const kl::int2 pos(i % 8, i / 8);
            target.drawImage(pos * squareSize, icons[int(pieces[i].type) - 1]);
        }
    }
}
