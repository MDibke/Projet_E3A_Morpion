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

void Game_init (void)
{
  // TODO: initialiser tous les modules
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
