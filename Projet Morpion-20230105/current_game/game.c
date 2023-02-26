/**
 * @file main.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "player_manager.h"
#include "board_view.h"
#include "board.h"

bool endGame = false;

void squareChangedCallback (Coordinate x, Coordinate y, PieceType piece)
{
  //affichage du plateau
  BoardView_displaySquare(x, y, piece);
}

void endOfGameCallback (GameResult winner)
{
  //affichage du gagnant
  BoardView_displayEndOfGame(winner);
  endGame = true;
}

void Game_init (void)
{
  //initialisation des modules
  Board_init(squareChangedCallback, endOfGameCallback);
  BoardView_init();
  PlayerManager_init();
}

void Game_free (void)
{
  //libération de la mémoire
  Board_free();
  PlayerManager_free();
  BoardView_free();
}

void Game_loop (void)
{
  //boucle de jeu   
	while (!endGame )
  {
    PlayerManager_oneTurn();
  }
 
  //attendre l'appui un touche pour quitter
  while (!kbhit());
}
