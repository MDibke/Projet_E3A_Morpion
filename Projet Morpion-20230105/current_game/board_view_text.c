#include "board_view.h"
#include <board.h>
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_TEXTUI

PieceType boardView[3][3];

void BoardView_init (void)
{
    // Initialisation du tableau
    for(unsigned char i = 0; i < 3; i++)
        for(unsigned char j = 0; j < 3; j++)
            boardView[i][j] = NONE;
}

void BoardView_free (void)
{
    // Libération mémoire
    free(boardView);
}

/**
 * Convertir un type de piece en un caractère
 *
 * @param [in] piece Piece
 *
 * @return un caractère grapique associé à cette pièce
 */
char BoardView_pieceToChar(PieceType piece) 
{
    switch (piece) 
    {
        case NONE: return ' ';
        case CROSS: return 'X';
        case CIRCLE: return 'O';
    }
}

void BoardView_displayAll (void)
{
// Afficher une grille complétée par les valeurs de view
    for(unsigned char i = 0; i < 3; i++) 
    {
        for(unsigned char j = 0; j < 3; j++) 
        {
            printf(" %c ", BoardView_pieceToChar(boardView[i][j]));
            printf(j < 2 ? "|" : "\n");
        }
        if(i < 2) 
            printf("---+---+---\n");
    }
    printf("\n");
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
    // Attribution d'une pièce dans view
    boardView[y][x] = kindOfPiece;
    BoardView_displayAll();
}

void BoardView_displayEndOfGame (GameResult result)
{
    switch (result) 
    {
        case CROSS_WINS:
            printf("---- Le joueur X a gagne ! ----\n\n");
            break;
        case CIRCLE_WINS:
            printf("---- Le joueur O a gagne ! ----\n\n");
            break;
        case DRAW:
            printf("---- Match nul ! ----\n\n");
            break;
  }
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
  switch (thisPlayer) 
  {
    case CROSS:
        printf("Au tour des croix\n");
        break;
    case CIRCLE:
        printf("Au tour des cercles\n");
        break;
    case NONE:
        fatalError("BoardView_displayPlayersTurn -> PLAYER: NONE");
        break;
  }
}

void BoardView_sayCannotPutPiece (void)
{
  printf("\nVous ne pouvez pas jouer ici !\n");
}

#endif // defined CONFIG_TEXTUI
