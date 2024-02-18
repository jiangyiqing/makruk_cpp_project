#include <iostream>
#include <vector>
#include <memory>

enum class Affiliation
{
    None,
    Player1,
    Player2
};

class Piece
{
protected:
    Affiliation piecestate; // Piece color
public:
    Piece(Affiliation pcolor) : piecestate(pcolor){}; // Constructor
    virtual ~Piece() {}                               // Virtual destructor for polymorphism
    virtual char getSymbol() const = 0;
};

class Pawn : public Piece
{
public:
    Pawn(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'P' : 'p'; // Example: Uppercase for white, lowercase for black
    };
};
class Rook : public Piece
{
public:
    Rook(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'R' : 'r';
    }
};

class Knight : public Piece
{
public:
    Knight(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'N' : 'n';
    }
};

class Bishop : public Piece
{
public:
    Bishop(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'S' : 's';
    }
};

class Advisor : public Piece
{
public:
    Advisor(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'M' : 'm';
    }
};

class Promoted_Pawn : public Piece
{
public:
    Promoted_Pawn(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'M' : 'm';
    }
};

class King : public Piece
{
public:
    King(Affiliation color) : Piece(color){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'K' : 'k';
    }
};

class Chessboard
{

private:
    std::vector<std::vector<std::shared_ptr<Piece> > > board;

public:
    Chessboard() : board(8, std::vector<std::shared_ptr<Piece> >(8, nullptr))
    {
        initBoard();
    };
    // Other methods like setupBoard, printBoard, etc.
    void initBoard()
    {
        // Initialize Pawns
        for (int i = 0; i < 8; ++i)
        {
            board[2][i] = std::make_shared<Pawn>(Affiliation::Player1); // Player1's pawns
            board[5][i] = std::make_shared<Pawn>(Affiliation::Player2); // Player2's pawns
        }
        // Initialize Rooks
        board[0][0] = board[0][7] = std::make_shared<Rook>(Affiliation::Player1);
        board[7][0] = board[7][7] = std::make_shared<Rook>(Affiliation::Player2);
        // Initialize Knights
        board[0][1] = board[0][6] = std::make_shared<Knight>(Affiliation::Player1);
        board[7][1] = board[7][6] = std::make_shared<Knight>(Affiliation::Player2);

        // Initialize Bishops
        board[0][2] = board[0][5] = std::make_shared<Bishop>(Affiliation::Player1);
        board[7][2] = board[7][5] = std::make_shared<Bishop>(Affiliation::Player2);
        // Initialize Kings
        board[0][3] = std::make_shared<King>(Affiliation::Player1);
        board[7][4] = std::make_shared<King>(Affiliation::Player2);
        // Initialize Advisors
        board[0][4] = std::make_shared<Knight>(Affiliation::Player1);
        board[7][3] = std::make_shared<Knight>(Affiliation::Player2);
    };
    std::shared_ptr<Piece> getPiece(int i, int j) const
    {
        if (i >= 0 && i < 8 && j >= 0 && j < 8)
        { // Ensure the indices are within the board bounds
            return board[i][j];
        }
        else
        {
            return nullptr; // Return nullptr if the indices are out of bounds
        }
    }

    // Test functions
    void printBoard()
    {
        for (const auto &row : board)
        {
            for (const auto &piece : row)
            {
                if (piece)
                    std::cout << piece->getSymbol() << ' ';
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }
    }
};

class ZoneOfControl
{
private:
    std::vector<std::vector<Affiliation> > zocboard;

public:
    ZoneOfControl() : zocboard(8, std::vector<Affiliation>(8, Affiliation::None)) {}

    // Method to update the control state of a square
    void setZoC(int x, int y, Affiliation state)
    {
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            zocboard[x][y] = state;
        }
    }

    // Method to get the control state of a square
    Affiliation getZoC(int x, int y) const
    {
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            return zocboard[x][y];
        }
        return Affiliation::None; // Return None for out-of-bounds queries
    };

    char controlStateToChar(Affiliation state) const
{
    switch (state)
    {
    case Affiliation::Player1:
        return 'X';
    case Affiliation::Player2:
        return 'O';
    default:
        return ' '; 
    }
}

    // Method to update control state of a square

    // Test functions:

    void printZoC() const
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                std::cout << ZoneOfControl::controlStateToChar(getZoC(i, j)) << ' ' << std::endl;
            }
        }
    }
};

// // Function to update the ZoC board based on current game state
// void updateZoC(/* Parameters such as the current game state */);

// // Function to check for check
// bool isCheck(/* Parameters such as the player's king position */);

// // Function to check for checkmate
// bool isCheckmate(/* Parameters such as the player's king position */);

int main()
{
    Chessboard chessboard;
    chessboard.printBoard();
    return 0;
}