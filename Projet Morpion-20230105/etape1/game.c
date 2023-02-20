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
  BoardView_displaySquare(x, y, piece);
}

void endOfGameCallback (GameResult winner)
{
  BoardView_displayWinner(winner);
  endGame = true;
}

void Game_init (void)
{
  Board_init(squareChangedCallback, endOfGameCallback);
  BoardView_init();
  PlayerManager_init();
}

void Game_free (void)
{
  Board_free();
  PlayerManager_free();
  BoardView_free();
}

void Game_loop (void)
{
	while (!endGame )
  {
    PlayerManager_oneTurn();
  }
}
