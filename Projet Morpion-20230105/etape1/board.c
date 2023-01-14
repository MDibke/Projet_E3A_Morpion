#include "board.h"
#include <assert.h>

#define CIRCLETEAM 'CIRCLE'
#define CROSSTEAM 'CROSS'
#define CROSSRESULT 'CROSS_WIN'
#define CIRCLERESULT 'CIRCLE_WIN'
#define DRAWRESULT 'DRAW'

unsigned char boardGame[3][3], lastGameResult;


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
  bool status = false;

  if((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2)||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(unsigned int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if((boardSquares[ligneColomn][ligneColomn] == boardSquares[CoordonateX][CoordonateY])||(boardSquares[2-ligneColomn][2-ligneColomn] == boardSquares[CoordonateX][CoordonateY]))
        status = true;
      else
        goto endDiagonalTest;
    }
  }
  goto endDiagonalTest;

  endDiagonalTest :
  return status; 
}

bool lignTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;
  
  for(unsigned int column = 0; column < 3; column++)
  {
    if(column != CoordonateY)
    {
      if(boardSquares[CoordonateX][column] == boardSquares[CoordonateX][CoordonateY])
        status = true;
      else
        goto endLignTest; 
    }   
  }
  goto endLignTest; 

  endLignTest :
  return status; 
}

bool columnTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;
  
  for(unsigned int lign = 0; lign < 3; lign++)
  {
    if(lign != CoordonateY)
    {
      if(boardSquares[lign][CoordonateY] == boardSquares[CoordonateX][CoordonateY])
        status = true;
      else
        goto endColumnTest;   
    }
  }
  goto endColumnTest;   

  endColumnTest :
  return status; 
}

bool fullTest(const PieceType boardSquares[3][3])
{
  bool status = false;

  for(unsigned int lign = 0; lign < 3; lign++)
  {
    for(unsigned int column = 0; column < 3; column++)
    {
      if(boardSquares[lign][column] != NONE)
        status = true;
      else
        goto endColumnTest;   
    }
  }
  goto endColumnTest;   

  endColumnTest :
  return status; 
}

static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  bool returnGameResult = false;

  if(gameResult == NONE)
  {
    if ((diagonalTest(boardSquares,lastChangeX,lastChangeY) == true)||(lignTest(boardSquares,lastChangeX,lastChangeY))||(columnTest(boardSquares,lastChangeX,lastChangeY)))
    {
      if(boardSquares[lastChangeX][lastChangeY] == CIRCLETEAM)
      {
        gameResult = CIRCLERESULT;
        returnGameResult = true;
      }
      else if(boardSquares[lastChangeX][lastChangeY] == CROSSTEAM)
      {
        gameResult = CROSSRESULT;
        returnGameResult = true;
      }
    }
    else if (fullTest(boardSquares) == true)
    {
      gameResult = DRAWRESULT;
      returnGameResult = true;
    }
  }

  return returnGameResult;
}
/*
void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  // TODO: à compléter
}

void Board_free ()
{
  // TODO: à compléter
}

SquareChangeCallback changeSquareBoard(Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  boardGame[x][y] = kindOfPiece;
}

EndOfGameCallback endGameBoard(unsigned char gameValueResult)
{
  return gameValueResult;
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  unsigned char returnedValue = "SQUARE_IS_NOT_EMPTY", gameResultGame = NONE;

  if(boardGame[x][y] != CROSSTEAM && boardGame[x][y] != CIRCLETEAM)
  {
    changeSquareBoard(x,y,kindOfPiece);
    returnedValue = "PIECE_IN_PLACE";
    isGameFinished(boardGame,x,y,gameResultGame);
    if((gameResultGame == CIRCLERESULT) || (gameResultGame == CROSSRESULT) || (gameResultGame == DRAWRESULT && fullTest(boardGame) == true))
    {
      endGameBoard(gameResultGame);
    }
  }

  return returnedValue;
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{

}
*/