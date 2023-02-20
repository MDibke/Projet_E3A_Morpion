/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_PLAYER_MANAGER_SCANF

PieceType player;

void PlayerManager_init (void)
{
  player = CIRCLE;
}

void PlayerManager_free (void)
{
  player = NONE;
}

void PlayerManager_oneTurn (void)
{
  int x, y, read = 0;
  bool ok = false;

    // Affiche le qui joueur joue
  BoardView_displayPlayersTurn(player);

  do {
        // Demande les coordonnées au format X,Y
      printf("Place ta piece en X,Y:\n");
      read = scanf("%d,%d", &x, &y);

        // Si incorrect ou si la case est déjà prise,
      if(read != 2 || x < 0 || x > 2 || y < 0 || y > 2 || Board_putPiece(x, y, player) != PIECE_IN_PLACE) {
            // Vider le buffer et afficher un message d'erreur
          char c;
          while ((c = getchar()) != '\n' && c != EOF);
          printf("\nPlacement  invalide...\n");
        }
        else ok = true;
    }
    while(!ok);

    // Prochain tour
    player = player == CIRCLE ? CROSS : CIRCLE;
}

#endif // defined CONFIG_PLAYER_MANAGER_SCANF
