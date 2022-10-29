#include <iostream>
#include <array>

#include "RandomNumbers.h"

using Square = uint_fast8_t;
using RankOrFile = uint_fast8_t;

using SideToMove = uint_fast8_t;

using BasePiece = uint_fast8_t;
using Piece = uint_fast8_t;

using ZobristKey = uint_fast64_t;

static constexpr SideToMove WHITE = 0;
static constexpr SideToMove BLACK = 1;

// Constants for non-coloured piece types
static constexpr BasePiece PAWN = 0;
//static constexpr BasePiece KNIGHT = 1;
//static constexpr BasePiece BISHOP = 2;
//static constexpr BasePiece ROOK = 3;
//static constexpr BasePiece QUEEN = 4;
static constexpr BasePiece KING = 5;

// Integer constants for coloured pieces
static constexpr Piece WHITE_PAWN = (2 * PAWN + WHITE);    // 0
//static constexpr Piece BLACK_PAWN = (2 * PAWN + BLACK);    // 1
//static constexpr Piece WHITE_KNIGHT = (2 * KNIGHT + WHITE);  // 2
//static constexpr Piece BLACK_KNIGHT = (2 * KNIGHT + BLACK);  // 3
//static constexpr Piece WHITE_BISHOP = (2 * BISHOP + WHITE);  // 4
//static constexpr Piece BLACK_BISHOP = (2 * BISHOP + BLACK);  // 5
//static constexpr Piece WHITE_ROOK = (2 * ROOK + WHITE);    // 6
//static constexpr Piece BLACK_ROOK = (2 * ROOK + BLACK);    // 7
//static constexpr Piece WHITE_QUEEN = (2 * QUEEN + WHITE);   // 8
//static constexpr Piece BLACK_QUEEN = (2 * QUEEN + BLACK);   // 9
//static constexpr Piece WHITE_KING = (2 * KING + WHITE);    // 10
static constexpr Piece BLACK_KING = (2 * KING + BLACK);    // 11

constexpr auto tab = "    ";

const std::array<std::string, 12> PieceNames = {
    "White Pawn",
    "Black Pawn",
    "White Knight",
    "Black Knight",
    "White Bishop",
    "Black Bishop",
    "White Rook",
    "Black Rook",
    "White Queen",
    "Black Queen",
    "White King",
    "Black King"
};

void generatePieceSquareKeys(RandomNumberGenerator& random)
{
    std::array<std::array<ZobristKey, 64>, 12> pieceSquareKeys{ 0 };

    std::cout << "static constexpr std::array<std::array<ZobristKey, 64>, 12> pieceSquareKeys = {" << '\n';

    for (Piece piece = WHITE_PAWN; piece <= BLACK_KING; ++piece)
    {
        std::cout << tab << "/* " << (int)piece << ' ' << PieceNames[piece] << " */" << '\n';

        for (RankOrFile rank = 0; rank < 8; ++rank)
        {
            std::cout << tab;

            for (RankOrFile file = 0; file < 8; ++file)
            {
                Square square = file + rank * 8;

                pieceSquareKeys[piece][square] = random.getRandom64BitNumber();

                if (piece == BLACK_KING &&
                    square == 63)
                    printf("0x%016llX /* %2d */", pieceSquareKeys[piece][square], square);
                else
                    printf("0x%016llX /* %2d */,", pieceSquareKeys[piece][square], square);
            }
            std::cout << '\n';
        }
    }

    std::cout << "};" << '\n';
    std::cout << '\n';
}

void generateEnPassantFileKeys(RandomNumberGenerator& random)
{
    std::array<ZobristKey, 8> enPassantFileKeys{ 0 };

    std::cout << "static constexpr std::array<ZobristKey, 8> enPassantFileKeys = {" << '\n';

    for (RankOrFile file = 0; file < 8; ++file)
    {
        enPassantFileKeys[file] = random.getRandom64BitNumber();

        std::cout << tab;
        if (file < 7)
            printf("0x%016llX /* %d */,\n", enPassantFileKeys[file], file);
        else
            printf("0x%016llX /* %d */\n", enPassantFileKeys[file], file);
    }

    std::cout << "};" << '\n';
    std::cout << '\n';
}

void generateCastlingKeys(RandomNumberGenerator& random)
{
    std::array<ZobristKey, 16> castlingKeys{ 0 };

    std::cout << "static constexpr std::array<ZobristKey, 16> castlingKeys = {" << '\n';

    for (uint_fast8_t i = 0; i < 16; ++i)
    {
        castlingKeys[i] = random.getRandom64BitNumber();

        std::cout << tab;
        if (i < 15)
            printf("0x%016llX /* %2d */,\n", castlingKeys[i], i);
        else
            printf("0x%016llX /* %2d */\n", castlingKeys[i], i);
    }

    std::cout << "};" << '\n';
    std::cout << '\n';
}

int main()
{
    // https://www.chessprogramming.org/Zobrist_Hashing

    RandomNumberGenerator random;

    std::cout << "#include <iostream>" << '\n';
    std::cout << "#include <array>" << '\n';
    std::cout << '\n';
    std::cout << "#include \"Types.h\"" << '\n';
    std::cout << '\n';
    std::cout << "namespace Zobrist {" << '\n';
    std::cout << '\n';

    generatePieceSquareKeys(random);

    generateEnPassantFileKeys(random);

    generateCastlingKeys(random);

    std::cout << "static constexpr ZobristKey blackSideKey = ";
    printf("0x%016llX;\n\n", random.getRandom64BitNumber());

    std::cout << "}" << '\n';
}
