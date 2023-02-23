#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_TEXTUI

#define BOARD_SIZE 3

void BoardView_init (void)
{
  for(int i = 0; i < BOARD_SIZE; i++)
  {
    for(int j = 0; j < BOARD_SIZE; j++) 
    {
      printf(" ");
      if(j<BOARD_SIZE-1) 
      {
        printf("|");
      }
    }
    if(i<BOARD_SIZE-1) 
    {
      printf("\n-----\n");
    }
  }
}

void BoardView_free (void)
{
  for(int i =0; i < 25; i++)
  {
    printf("\n");
  }
}

void BoardView_displayAll (void)
{
  // TODO: à compléter
  for(int i = 0; i < BOARD_SIZE; i++)
  {
    for(int j = 0; j < BOARD_SIZE; j++) 
    {
      if(Board_getSquareContent(i, j) == CIRCLE) 
      {
        printf("O");
      }
      else if(Board_getSquareContent(i, j) == CROSS) 
      {
        printf("X");
      }
      else 
      {
        printf(" ");
      }

      if(j<BOARD_SIZE-1) 
      {
        printf("|");
      }
    }    
    if(i<BOARD_SIZE-1) 
    {
      printf("\n-----\n");
    }
  }
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  for(int i = 0; i < BOARD_SIZE; i++)
  {
    for(int j = 0; j < BOARD_SIZE; j++) 
    {
      if(i == x && j == y) 
      {
        if(kindOfPiece == CIRCLE) 
        {
          printf("O");
        }
        else if(kindOfPiece == CROSS) 
        {
          printf("X");
        }
        else 
        {
          printf(" ");
        }
      }
      else 
      {
        printf(" ");
      }
      
      if(j<BOARD_SIZE-1) 
      {
        printf("|");
      }
    }
    if(i<BOARD_SIZE-1) 
    {
      printf("\n-----\n");
    }
  }
}

void BoardView_displayEndOfGame (GameResult result)
{
  if(result == CIRCLE_WINS) 
  {
    printf("\nLe joueur O a gagné !\n");
  }
  else if(result == CROSS_WINS) 
  {
    printf("\nLe joueur X a gagné !\n");
  }
  else if(result == DRAW) 
  {
    printf("\nMatch nul !\n");
  }
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
  if(thisPlayer == CIRCLE) 
  {
    printf("\nAu tour du joueur O\n");
  }
  else if(thisPlayer == CROSS) 
  {
    printf("\nAu tour du joueur X\n");
  }
}

void BoardView_sayCannotPutPiece (void)
{
  printf("\nVous ne pouvez pas jouer ici !\n");
}

#endif // defined CONFIG_TEXTUI
