#include "board.h"
#include <assert.h>
static PieceType (boardGames)[3];
/**
 * Check if the game has to be ended. Only alignment from the last
 * modified square are checked.
 *
 * @param [in] boardSquares the board to check
 * @param [in] lastChangeX the colum where the last piece has been put
 * @param [in] lastChangeY the row where the last piece has been put
 * @param [out] gameResult the winning status if the game has ended (value is not set if
 * the game is not finished)
 *
 * @pre lastChangeX must be in [0..2]
 * @pre lastChangeY must be in [0..2]
 * @pre gameResult must point on an allocated GameResult variable
 *
 * @return a boolean that tells if the game is finished
 */
static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  const char last_play = boardSquares[lastChangeX][lastChangeY];
  
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  boardGames = calloc(3, sizeofboard);

    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            board[i][j] = NONE;
}

void Board_free ()
{
 free(boardGames);
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (boardGames[i][j] == NONE)
        boardGames [x][y] = kindOfPiece;
      else
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  // TODO: à compléter
}