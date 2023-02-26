#include "board.h"
#include <assert.h>

PieceType boardGames[3][3];
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
bool diagonal1Test(Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  //test si les dernières coordonnées du points joué sont dans un des coin du plateau ou au centre
  if(((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2))||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(unsigned int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if(Board_getSquareContent(ligneColomn,ligneColomn) != NONE)
      {  
        if(Board_getSquareContent(ligneColomn,ligneColomn) == Board_getSquareContent(CoordonateX,CoordonateY))
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
bool diagonal2Test(Coordinate CoordonateX, Coordinate CoordonateY)
{
  bool status = false;

  //test si les dernières coordonnées du points joué sont dans un des coin du plateau ou au centre
  if(((CoordonateX == 0 || CoordonateX == 2)&&(CoordonateY == 0 || CoordonateY == 2))||(CoordonateX == 1 && CoordonateY == 1))
  { 
    for(unsigned int ligneColomn = 0; ligneColomn < 3; ligneColomn++)
    {
      if(Board_getSquareContent((2-ligneColomn),ligneColomn) != NONE)
      {  
        if(Board_getSquareContent(2-ligneColomn,ligneColomn) == Board_getSquareContent(CoordonateX,CoordonateY))
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
bool columnTest(Coordinate CoordonateX, Coordinate CoordonateY)
{
	bool status = false;

	for(Coordinate column = 0; column < 3; column++)
	{
		if(column != CoordonateY)
		{
			if(Board_getSquareContent(CoordonateX,column) != NONE)
			{
				if(Board_getSquareContent(CoordonateX,column) == Board_getSquareContent(CoordonateX,CoordonateY))
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
bool lignTest(Coordinate CoordonateX, Coordinate CoordonateY)
{
	bool status = false;

	for(Coordinate lign = 0; lign < 3; lign++)
	{
		if(lign != CoordonateX)
		{
			if(Board_getSquareContent(lign,CoordonateY) != NONE)
			{
				if(Board_getSquareContent(lign,CoordonateY) == Board_getSquareContent(CoordonateX,CoordonateY))
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
bool fullTest()
{
  bool status = false;

  for(unsigned int lign = 0; lign < 3; lign++)
  {
    for(unsigned int column = 0; column < 3; column++)
    {
      if(Board_getSquareContent(lign,column) != NONE)
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

static bool isGameFinished (Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  bool returnGameResult = false,
  //récupère les états des cases pouvant finir une partie par rapport au dernier point joué
  diagonalValue1 = diagonal1Test(lastChangeX,lastChangeY),
  diagonalValue2 = diagonal2Test(lastChangeX,lastChangeY),
  lignValue = lignTest(lastChangeX,lastChangeY),
  columnValue = columnTest(lastChangeX,lastChangeY), 
  fullBoardValue = fullTest();

  *gameResult = DRAW;

  //vérifie si l'une des variable est égal à true
  if ((diagonalValue1 == true)||(diagonalValue2 == true)||(lignValue == true)||(columnValue == true))
  {
    //retourne le gagnant à partir du dernier point joué
    if(Board_getSquareContent(lastChangeX,lastChangeY) == CIRCLE)
      *gameResult = CIRCLE_WINS;
    else if(Board_getSquareContent(lastChangeX,lastChangeY)== CROSS)
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
  //initialisation du plateau de jeu
  for(unsigned int i = 0; i < 3; i++)
    for(unsigned int j = 0; j < 3; j++)
        boardGames[i][j] = NONE;
//initialisation des callbacks
  squareChange = onSquareChange;
  endOfGame = onEndOfGame;
}

void Board_free ()
{
  //libération de la mémoire
    free(boardGames);
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  //verifier si la case est vide
  if (Board_getSquareContent(x,y) != NONE ) 
    return SQUARE_IS_NOT_EMPTY;
  //placer la piece et mettre a jour l'interface
  boardGames [x][y] = kindOfPiece;
  squareChange(x, y, kindOfPiece);
  // mise en attente du resultat de la partie
  GameResult resultofGame = DRAW;
  // verifier si la partie est finie
  if (isGameFinished(x, y, &resultofGame))   
    endOfGame(resultofGame);
  return PIECE_IN_PLACE;
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  //retourne le contenu de la case
  return boardGames[x][y];
}
