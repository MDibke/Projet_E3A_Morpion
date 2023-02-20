#include "board.h"
#include <assert.h>

static PieceType (*boardGames)[3];
SquareChangeCallback squareChange;
EndOfGameCallback endOfGame;
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

//Test la diagonale partant du haut gauche jusqu'au bas droit du plateau et retounr TRUE si il y a trois même signe sur cette diagonale
bool diagonal1Test(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  //test si les dernières coordonnées du points joué sont dans un des coin du plateau ou au centre
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

//Test la diagonale partant du haut droit jusqu'au bas gauche du plateau et retounr TRUE si il y a trois même signe sur cette diagonale
bool diagonal2Test(const PieceType boardSquares[3][3], Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  //test si les dernières coordonnées du points joué sont dans un des coin du plateau ou au centre
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

//Test la colonne du dernier point joué du plateau et retounr TRUE si il y a trois même signe sur cette colonne
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

//Test la ligne du dernier point joué du plateau et retounr TRUE si il y a trois même signe sur cette ligne
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

//test si le plateau est plein et ne permet ps de rejouer
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
  //récupère les états des cases pouvant finir une partie par rapport au dernier point joué
  diagonalValue1 = diagonal1Test(boardSquares,lastChangeX,lastChangeY),
  diagonalValue2 = diagonal2Test(boardSquares,lastChangeX,lastChangeY),
  lignValue = lignTest(boardSquares,lastChangeX,lastChangeY),
  columnValue = columnTest(boardSquares,lastChangeX,lastChangeY), 
  fullBoardValue = fullTest(boardSquares);

  *gameResult = DRAW;

  //vérifie si l'une des variable est égal à true
  if ((diagonalValue1 == true)||(diagonalValue2 == true)||(lignValue == true)||(columnValue == true))
  {
    //retourne le gagnant à partir du dernier point joué
    if(boardSquares[lastChangeX][lastChangeY] == CIRCLE)
      *gameResult = CIRCLE_WINS;
    else if(boardSquares[lastChangeX][lastChangeY] == CROSS)
      *gameResult = CROSS_WINS;

    //retourne que la partie est fini
    returnGameResult = true;
  }
  //retourne que la partie est fini lorsque toute les cases de la grille est pleine et retounre comme gagnant DRAW
  else if (fullBoardValue == true)
  {
    returnGameResult = true;
  }

  return returnGameResult;
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  boardGames = calloc(3, sizeof(boardGames));

    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            boardGames[i][j] = NONE;

  squareChange = onSquareChange;
  endOfGame = onEndOfGame;
}

void Board_free ()
{
 free(boardGames);
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  //verifier si la case est vide
  if (boardGames[x][y] != NONE ) return SQUARE_IS_NOT_EMPTY;
  //placer la piece et mettre a jour l'interface
  boardGames [x][y] = kindOfPiece;
  squareChange(x, y, kindOfPiece);
  // mise en attente du resultat de la partie
  GameResult resultofGame = DRAW;
  // verifier si la partie est finie
  if (isGameFinished(boardGames, x, y, &resultofGame))   
    endOfGame(resultofGame);
  return PIECE_IN_PLACE;
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  return boardGames[x][y];
}
