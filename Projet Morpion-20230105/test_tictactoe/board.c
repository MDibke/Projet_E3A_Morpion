#include "board.h"
#include <assert.h>

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

bool diagonal1Test(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  if(((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2))||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(unsigned int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if(boardSquares[ligneColomn][ligneColomn] != NONE)
      {  
        if(boardSquares[ligneColomn][ligneColomn] == boardSquares[CoordonateX][CoordonateY])
          status = true;
        else
        {
          status = false;
          goto endDiagonalTest;
        }
      }
      else 
      {
          status = false;
          goto endDiagonalTest;
      }
    }
  }
  goto endDiagonalTest;

  endDiagonalTest :
  return status; 
}

bool diagonal2Test(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  if(((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2))||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(unsigned int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if(boardSquares[2-ligneColomn][ligneColomn] != NONE)
      {  
        if(boardSquares[2-ligneColomn][ligneColomn] == boardSquares[CoordonateX][CoordonateY])
          status = true;
        else
        {
          status = false;
          goto endDiagonalTest;
        }
      }
      else 
      {
        status = false;
        goto endDiagonalTest;
      }
    }
  }
  goto endDiagonalTest;

  endDiagonalTest :
  return status; 
}

bool columnTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
	bool status = false;

	for(Coordinate column = 0; column < 3; column++)
	{
		if(column != CoordonateY)
		{
			if(boardSquares[CoordonateX][column] != NONE)
			{
				if(boardSquares[CoordonateX][column] == boardSquares[CoordonateX][CoordonateY])
					status = true;
				else
				{
					status = false;
					goto endColumnTest;
				}
			}
			else
			{
				status = false;
				goto endColumnTest;
			}
		}
	}
	goto endColumnTest;

	endColumnTest:
	return status;
}

bool lignTest(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
	bool status = false;

	for(Coordinate lign = 0; lign < 3; lign++)
	{
		if(lign != CoordonateX)
		{
			if(boardSquares[lign][CoordonateY] != NONE)
			{
				if(boardSquares[lign][CoordonateY] == boardSquares[CoordonateX][CoordonateY])
					status = true;
				else
				{
					status = false;
					goto endLignTest;
				}
			}
			else
			{
				status = false;
				goto endLignTest;
			}
		}
	}
	goto endLignTest;

	endLignTest:
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
      {
        status = false;
        goto endColumnTest;   
      }
    }
  }
  goto endColumnTest;   

  endColumnTest :
  return status; 
}

static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  bool returnGameResult = false,
  diagonalValue1 = diagonal1Test(boardSquares,lastChangeX,lastChangeY),
  diagonalValue2 = diagonal2Test(boardSquares,lastChangeX,lastChangeY),
  lignValue = lignTest(boardSquares,lastChangeX,lastChangeY),
  columnValue = columnTest(boardSquares,lastChangeX,lastChangeY), 
  fullBoardValue = fullTest(boardSquares);

  *gameResult = DRAW;

  if ((diagonalValue1 == true)||(diagonalValue2 == true)||(lignValue == true)||(columnValue == true))
  {
    if(boardSquares[lastChangeX][lastChangeY] == CIRCLE)
      *gameResult = CIRCLE_WINS;
    else if(boardSquares[lastChangeX][lastChangeY] == CROSS)
      *gameResult = CROSS_WINS;
    returnGameResult = true;
  }
  else if (fullBoardValue == true)
  {
    returnGameResult = true;
  }

  return returnGameResult;
}
/*
void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  // TODO: ?? compl??ter
}

void Board_free ()
{
  // TODO: ?? compl??ter
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