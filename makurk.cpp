#include <iostream>
#include <vector>
#include <memory>

class Piece;
class Chessboard;

enum class Affiliation
{
    None = 0,
    Player1 = 1,
    Player2 = 2,
    Both = 3
};

Affiliation OtherAff(Affiliation aff)
{
    if (aff == Affiliation::Player1)
    {
        return Affiliation::Player2;
    }
    if (aff == Affiliation::Player2)
    {
        return Affiliation::Player1;
    }
    return Affiliation::None;
}

char controlStateToChar(Affiliation state)
{
    switch (state)
    {
    case Affiliation::Player1:
        return 'X';
    case Affiliation::Player2:
        return 'O';
    case Affiliation::Both:
        return '*';
    default:
        return '.';
    }
}

int controlStateToInt(Affiliation state)
{
    switch (state)
    {
    case Affiliation::Player1:
        return 1;
    case Affiliation::Player2:
        return -1;
    default:
        return 0;
    }
}

class Piece
{
protected:
    Affiliation piecestate; // Piece color
    Chessboard& board;
public:
    Piece(Affiliation pcolor, Chessboard& board) : piecestate(pcolor), board(board){}; // Constructor
    virtual ~Piece() {}                               // Virtual destructor for polymorphism
    virtual char getSymbol() const = 0;
    Affiliation getAffiliation() const
    {
        return piecestate;
    }
    virtual std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const = 0;

};

class Pawn : public Piece
{
public:
    Pawn(Affiliation color, Chessboard& board) : Piece(color,board){};

    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'P' : 'p'; // Example: Uppercase for white, lowercase for black
    };

    virtual std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override
    {
        std::vector<std::pair<int, int>> ZoCPawn;
        int sideModifier = controlStateToInt(piecestate);



                ZoCPawn.push_back({i + sideModifier, j + 1});
            

                ZoCPawn.push_back({i + sideModifier, j - 1});

        
        return ZoCPawn;
    }
};

class Rook : public Piece
{
public:
    Rook(Affiliation color, Chessboard& board) : Piece(color,board){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'R' : 'r';
    };
    void ZoCLine(int i, int j, int di, int dj, std::vector<std::pair<int, int>>& ZoCL, const Chessboard& board) const;
    std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override;

};

class Knight : public Piece
{
public:
    Knight(Affiliation color, Chessboard& board) : Piece(color,board){};

    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'N' : 'n';
    };

    std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override
    {
        std::vector<std::pair<int, int>> ZoCKnight;
        ZoCKnight.push_back({i+1, j+2});
        ZoCKnight.push_back({i+1, j-2});
        ZoCKnight.push_back({i-1, j+2});
        ZoCKnight.push_back({i-1, j-2});

        ZoCKnight.push_back({i+2, j+1});
        ZoCKnight.push_back({i+2, j-1});
        ZoCKnight.push_back({i-2, j+1});
        ZoCKnight.push_back({i-2, j-1});


        return ZoCKnight;
    }
};

class Bishop : public Piece
{
public:
    Bishop(Affiliation color, Chessboard& board) : Piece(color,board){};

    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'S' : 's';
    }

    std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override
    {
        std::vector<std::pair<int, int>> ZoCBishop;
        int sideModifier = controlStateToInt(piecestate);

        ZoCBishop.push_back({i + sideModifier, j + 1});

        ZoCBishop.push_back({i + sideModifier, j - 1});

        ZoCBishop.push_back({i + sideModifier, j});

        ZoCBishop.push_back({i - sideModifier, j + 1});

        ZoCBishop.push_back({i - sideModifier, j - 1});

        return ZoCBishop;
    }
};

class Advisor : public Piece
{
public:
    Advisor(Affiliation color, Chessboard& board) : Piece(color,board){};

    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'M' : 'm';
    }

    std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override
    {
        std::vector<std::pair<int, int>> ZoCAdvisor;

        ZoCAdvisor.push_back({i + 1, j + 1});

        ZoCAdvisor.push_back({i + 1, j - 1});

        ZoCAdvisor.push_back({i - 1, j + 1});

        ZoCAdvisor.push_back({i - 1, j - 1});

        return ZoCAdvisor;
    }
};


// class Promoted_Pawn : public Piece
// {
// public:
//     Promoted_Pawn(Affiliation color, Chessboard* board) : Piece(color,board){};
//     char getSymbol() const override
//     {
//         return (piecestate == Affiliation::Player1) ? 'M' : 'm';
//     }
// };

class King : public Piece
{
public:
    King(Affiliation color, Chessboard& board) : Piece(color,board){};
    char getSymbol() const override
    {
        return (piecestate == Affiliation::Player1) ? 'K' : 'k';
    };

        std::vector<std::pair<int, int>> updateZoC(int i, int j, const Chessboard& board) const override
    {
        std::vector<std::pair<int, int>> ZoCKing;
        ZoCKing.push_back({i+1, j+1});
        ZoCKing.push_back({i+1, j-1});
        ZoCKing.push_back({i-1, j+1});
        ZoCKing.push_back({i-1, j-1});

        ZoCKing.push_back({i, j+1});
        ZoCKing.push_back({i, j-1});
        ZoCKing.push_back({i+1, j});
        ZoCKing.push_back({i-1, j});


        return ZoCKing;
    }
};


class Chessboard
{

private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;

public:
    Chessboard() : board(8, std::vector<std::shared_ptr<Piece>>(8, nullptr))
    {
        initBoard();
    };
    // Other methods like setupBoard, printBoard, etc.
    void initBoard()
    {
        // Initialize Pawns
        for (int i = 0; i < 8; ++i)
        {
            board[2][i] = std::make_shared<Pawn>(Affiliation::Player1,*this); // Player1's pawns
            board[5][i] = std::make_shared<Pawn>(Affiliation::Player2,*this); // Player2's pawns
        }
        // Initialize Rooks
        board[0][0] = board[0][7] = std::make_shared<Rook>(Affiliation::Player1,*this);
        board[7][0] = board[7][7] = std::make_shared<Rook>(Affiliation::Player2,*this);
        // Initialize Knights
        board[0][1] = board[0][6] = std::make_shared<Knight>(Affiliation::Player1,*this);
        board[7][1] = board[7][6] = std::make_shared<Knight>(Affiliation::Player2,*this);

        // Initialize Bishops
        board[0][2] = board[0][5] = std::make_shared<Bishop>(Affiliation::Player1,*this);
        board[7][2] = board[7][5] = std::make_shared<Bishop>(Affiliation::Player2,*this);
        // Initialize Kings
        board[0][3] = std::make_shared<King>(Affiliation::Player1,*this);
        board[7][4] = std::make_shared<King>(Affiliation::Player2,*this);
        // Initialize Advisors
        board[0][4] = std::make_shared<Advisor>(Affiliation::Player1,*this);
        board[7][3] = std::make_shared<Advisor>(Affiliation::Player2,*this);
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
        std::cout << "------Printing Chessboard------" << std::endl;
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
        std::cout << "------Chessboard Printed------" << std::endl;
    }
};

void Rook::ZoCLine(int i,int j,int di, int dj, std::vector<std::pair<int, int>>& ZoCL, const Chessboard& board) const{
        int k = 1;
        while (board.getPiece(i+k*di,j+k*dj) == nullptr && i+k*di < 8 && i+k*di >=0 && j+k*dj < 8 && j+k*dj >= 0)
        { 
            ZoCL.push_back({i+k*di, j+k*dj});
            k++;
        }
        
    }

std::vector<std::pair<int, int>> Rook::updateZoC(int i, int j, const Chessboard& board) const
    {
        std::vector<std::pair<int, int>> ZoCRook;
        ZoCLine(i,j,1,0,ZoCRook, board);
        ZoCLine(i,j,0,1,ZoCRook, board);
        ZoCLine(i,j,-1,0,ZoCRook, board);
        ZoCLine(i,j,0,-1,ZoCRook, board);
        return ZoCRook;
    }

class ZoneOfControl
{
private:
    std::vector<std::vector<Affiliation>> zocboard;

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

    // Method to update parts of the board
    void piecewiseZoC(std::vector<std::pair<int, int>> pieceZoC, Affiliation aff)
    {
        // Test function
        if (aff == Affiliation::None || aff == Affiliation::Both)
        {
            std::cout << "piecewiseZoC input affiliation error!" << std::endl;
        }

        for (const auto &element : pieceZoC)
        {
            int i = element.first;
            int j = element.second;
            if (getZoC(i, j) == Affiliation::None)
            {
                setZoC(i, j, aff);
            }
            else if (getZoC(i, j) == OtherAff(aff))
            {
                setZoC(i, j, Affiliation::Both);
            }
        }
    }

    // Method to update cs of the entire board
    void updateAllZoC(const Chessboard& board)
    {
        std::cout << "Updating All ZoC..." << std::endl;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                const std::shared_ptr<Piece> piece = board.getPiece(i, j);
                if (piece)
                {
                    std::vector<std::pair<int, int>> pieceZoC = piece->updateZoC(i, j,board);
                    piecewiseZoC(pieceZoC, piece->getAffiliation());
                }
            }
        }
    }

    // Test functions:

    void printZoC() const
    {
        std::cout << "------Printing ZoC Board------" << std::endl;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                std::cout << controlStateToChar(getZoC(i, j)) << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "------ZoC Board Printed------" << std::endl;

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
    std::cout << "!!!!!" << std::endl;
    Chessboard chessboard;
    chessboard.printBoard();
    ZoneOfControl ZoC;
    ZoC.updateAllZoC(chessboard);
    ZoC.printZoC();

    return 0;
}