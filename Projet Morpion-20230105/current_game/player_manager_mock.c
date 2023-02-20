/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "player_manager.h"
#include <assert.h>
#include <stdio.h>


#if defined CONFIG_PLAYER_MANAGER_MOCK

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
    if(player == CIRCLE) {
        Board_putPiece(0, 0, player);
        player = CROSS;
    }
    else {
        Board_putPiece(1, 0, player);
        player = CIRCLE;
    }
}

#endif //  #if defined CONFIG_PLAYER_MANAGER_MOCK
