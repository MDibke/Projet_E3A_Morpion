#include "board.h"
#include <assert.h>

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

bool diagonalTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false, test_status = false;

  if((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2)||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if((boardSquares[ligneColomn][ligneColomn] == boardSquares[CoordonateX][CoordonateY])||(boardSquares[2-ligneColomn][2-ligneColomn] == boardSquares[CoordonateX][CoordonateY]))
        status = true;
      else
        goto endDiagonalTest;
    }
  }

  endDiagonalTest :
  return status; 
}

bool lignTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false, test_status = false;
  
  for(int column = 0; column < 3; column++)
  {
    if(column != CoordonateY && (boardSquares[CoordonateX][column]))
      status = true;
    else
      goto endLignTest;   
  }

  endLignTest :
  return status; 
}

bool columnTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false, test_status = false;
  
  for(int lign = 0; lign < 3; lign++)
  {
    if(lign != CoordonateY && (boardSquares[lign][CoordonateY]))
      status = true;
    else
      goto endColumnTest;   
  }

  endColumnTest :
  return status; 
}

static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  if ((diagonalTest(boardSquares,lastChangeX,lastChangeY) == true)||(lignTest(boardSquares,lastChangeX,lastChangeY))||(columnTest(boardSquares,lastChangeX,lastChangeY)))
  {
    gameResult = true;
    goto end;
  }  

  end :
  return *gameResult;
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  // TODO: à compléter
}

void Board_free ()
{
  // TODO: à compléter
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  // TODO: à compléter
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  // TODO: à compléter
}
